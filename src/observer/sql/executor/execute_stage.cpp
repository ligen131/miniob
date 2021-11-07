/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      RC rc = do_select(current_db, sql, exe_event->sql_event()->session_event());
      if(rc != RC::SUCCESS){
        const char *response = "FAILURE\n";
        session_event->set_response(response);
      }
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "drop table `table name`;\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table` [where `column`=`value`];\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

/*
RC do_multi_tables_select_DFS(Trx *trx, Session *session, const Selects selects, const char *db, int now) {
  RC rc = RC::SUCCESS;
  if(now > total_table) {
    // Multi print
    return RC::SUCCESS;
  }

  std::vector<SelectExeNode *> select_nodes;
  const char *table_name = Multi_tables_list[now]->name();
  SelectExeNode *select_node = new SelectExeNode;
  rc = create_selection_executor(trx, selects, db, table_name, *select_node);
  if (rc != RC::SUCCESS) {
    delete select_node;
    for (SelectExeNode *& tmp_node: select_nodes) {
      delete tmp_node;
    }
    end_trx_if_need(session, trx, false);
    return rc;
  }
  select_nodes.push_back(select_node);
  delete select_node;

  int num2, i = 0;
  for(std::vector<Table *>::iterator iter = Table_To_Table[now].begin(); iter != Table_To_Table[now].end(); iter++, ++i){
    num2 = Table_Map[(*iter)];

  }
}
*/

// Table *Multi_tables_list[MAX_NUM + 1];
std::vector<Table *>Table_To_Table[MAX_NUM];
// std::vector<Table *>Empty_Table;
std::vector<size_t>Field_To_Field_from[MAX_NUM];
std::vector<size_t>Field_To_Field_targ[MAX_NUM];
// std::vector<size_t>Empty_FieldMeta;
std::unordered_map<Table *,size_t>Table_Map;
// std::unordered_map<Table *,size_t>Empty_Table_Map;
std::vector<TupleSet> tuple_sets_;
// TupleSet multi_tables_tuple_set;
// std::vector<TupleSet> Empty_tuple_set;
std::vector<CompOp> Multi_tables_compop_[MAX_NUM];
// std::vector<CompOp> Empty_compop;
size_t total_table;
bool tuple_filter[MAX_NUM][MAX_NUM];
int DFS_tree[MAX_NUM];
TupleSet multi_tables_tuple_set;
bool multi_tables_filter(int cmp_result,CompOp comp_op_) {
  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

// Tuple do_multi_tables_select_DFS_tuple;
RC do_multi_tables_select_DFS(size_t now, TupleSet &multi_tables_tuple_set) {
  LOG_INFO("DFS in %d.", now);
  if (now == total_table){
    LOG_INFO("Find one acceptable answer. %d %d",DFS_tree[0], DFS_tree[1]);
    Tuple tuple;
    for (size_t i = 0; i < total_table; ++i) {
      // std::vector<std::shared_ptr<TupleValue>> value_;
      // value_.emplace_back(tuple_sets_[i].tuples()[DFS_tree[i]].values());
      // size_t sz = value_.size();
      // for (size_t j = 0; j < sz; ++j) {
      //   if(tuple_filter[i][j]) tuple.add(value_[j]);
      // }
      int j = 0;
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = tuple_sets_[i].tuples()[DFS_tree[i]].values().begin();
            iter != tuple_sets_[i].tuples()[DFS_tree[i]].values().end(); ++iter, ++j) {
              if(tuple_filter[i][j]) tuple.add((*iter));
            }
    }
    multi_tables_tuple_set.add(std::move(tuple));
    return RC::SUCCESS;
  }
  
  int now_tuple_index = 0;
  for (std::vector<Tuple>::const_iterator iter = tuple_sets_[now].tuples().begin(); iter != tuple_sets_[now].tuples().end(); ++iter, ++now_tuple_index) {
    int i = 0, num, f, t;
    bool ok_ = 1;
    for (std::vector<Table *>::iterator it = Table_To_Table[now].begin(); it != Table_To_Table[now].end(); ++it, ++i) {
      num = Table_Map[(*it)] - 1;
      f = Field_To_Field_from[now][i];
      t = Field_To_Field_targ[now][i];
      // LOG_INFO("num = %d, f = %d, t = %d %d %d %d.",num,DFS_tree[num],f,t,tuple_sets_[num].tuples()[DFS_tree[num]].values()[f].get()->compare(*((*iter).values()[t].get())),Multi_tables_compop_[now][i]);
      if (!multi_tables_filter(tuple_sets_[num].tuples()[DFS_tree[num]].values()[f].get()->compare(*((*iter).values()[t].get())), Multi_tables_compop_[now][i])){
        ok_ = 0;
        break;
      }
    }
    if (ok_) {
      DFS_tree[now] = now_tuple_index;
      // for (size_t k = 0; k < (*iter).values().size(); ++k) {
      //   if(tuple_filter[now][k]) do_multi_tables_select_DFS_tuple.add((*iter).values()[k]);
      // }
      do_multi_tables_select_DFS(now + 1, multi_tables_tuple_set);
      // for (size_t k = 0; k < (*iter).values().size(); ++k) {
      //   if(tuple_filter[now][k]) do_multi_tables_select_DFS_tuple.pop_back_();
      // }
    }
  }
  return RC::SUCCESS;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) ;

RC multi_tables_select_init(Trx *trx, Session *session, const Selects &selects, const char *db, TupleSet &multi_tables_tuple_set) {
  LOG_INFO("Start to init multi tables.");
  RC rc = RC::SUCCESS;

  Table_Map.clear();
  // TupleSet ts;
  // multi_tables_tuple_set = std::move(ts); // 注意：不可用！会段错误
  multi_tables_tuple_set.clear();
  memset(tuple_filter, 0, sizeof(tuple_filter));
  // memset(&multi_tables_tuple_set, 0, sizeof(multi_tables_tuple_set));
  
  // 取出所有table
  TupleSchema schema;
  total_table = 0;
  for (int i = selects.relation_num - 1;i >= 0 ; --i){
    const char *table_name = selects.relations[i];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    if (nullptr == table) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    if (!Table_Map[table]) {
      Table_Map[table] = ++total_table;
      Table_To_Table[total_table].clear();
      Field_To_Field_from[total_table].clear();
      Field_To_Field_targ[total_table].clear();
      // Multi_tables_list[total_table] = table;
      Multi_tables_compop_[total_table].clear();
      if(selects.attr_num == 1 && nullptr == selects.attributes[0].relation_name && strcmp("*", selects.attributes[0].attribute_name) == 0) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        for (int j = 1; j < table->table_meta().field_num(); ++j) {
          tuple_filter[total_table - 1][j - 1] = 1;
        }
      }
    }
  }

  int num;
  if(!(selects.attr_num == 1 && strcmp("*", selects.attributes[0].attribute_name) == 0)) {
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      Table * table = DefaultHandler::get_default().find_table(db,selects.attributes[i].relation_name);
      num = Table_Map[table];
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        int sz = table->table_meta().field_num();
        for (int j = 1; j < sz; ++j) {
          tuple_filter[num - 1][j - 1] = 1;
        }
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        rc = schema_add_field(table, attr.attribute_name, schema);
        tuple_filter[num - 1][table->real_table_meta().get_index_by_field(attr.attribute_name) - 1] = 1;
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }
  multi_tables_tuple_set.set_schema(schema);

  // table之间的filter
  Table * table1;
  Table * table2;
  Table * t_table;
  int field_meta1, field_meta2, t_field_meta;
  int num2;
  for (size_t i = 0;i < selects.condition_num;++i) {
    const Condition &condition = selects.conditions[i];
    if(condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
        strcmp(condition.left_attr.relation_name, condition.right_attr.relation_name) != 0) {

        table1 = DefaultHandler::get_default().find_table(db, condition.left_attr.relation_name);
        if (nullptr == table1) {
          LOG_WARN("No such table [%s] in db [%s]", condition.left_attr.relation_name, db);
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        table2 = DefaultHandler::get_default().find_table(db, condition.right_attr.relation_name);
        if (nullptr == table2) {
          LOG_WARN("No such table [%s] in db [%s]", condition.right_attr.relation_name, db);
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        field_meta1 = table1->real_table_meta().get_index_by_field(condition.left_attr.attribute_name);
        if (-1 == field_meta1) {
          LOG_WARN("No such field. %s.%s", table1->name(), condition.left_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        field_meta2 = table2->real_table_meta().get_index_by_field(condition.right_attr.attribute_name);
        if (-1 == field_meta2) {
          LOG_WARN("No such field. %s.%s", table2->name(), condition.left_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        if (Table_Map[table1] > Table_Map[table2]) {
          t_table = table1; t_field_meta = field_meta1;
          table1 = table2;  field_meta1 = field_meta2;
          table2 = t_table; field_meta2 = t_field_meta;
        }
        num2 = Table_Map[table2];
        Table_To_Table[num2 - 1].push_back(table1);
        Field_To_Field_from[num2 - 1].push_back(field_meta1 - 1);
        Field_To_Field_targ[num2 - 1].push_back(field_meta2 - 1);
        Multi_tables_compop_[num2 - 1].push_back(condition.comp);
      }
  }

  LOG_INFO("End of init multi tables.");
  return RC::SUCCESS;
}

RC do_aggregation_func_select(TupleSet &tupleset, const Selects &selects, std::ostream &os) {
  LOG_INFO("Start to do aggr func.");

  // 输出表头
  for (int i = selects.attr_num - 1; i >= 0; --i) {
    switch(selects.attributes[i].agg){
      case COUNT:{
        os << "count(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case MAX:{
        os << "max(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case MIN:{
        os << "min(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case AVG:{
        os << "avg(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      default:{
        LOG_ERROR("Invalid Input.");
        return RC::GENERIC_ERROR;
      }
      break;
    }
    if (i != 0) os << " | "; else os << std::endl;
  }
  
  // 输出结果
  for (int i = selects.attr_num - 1; i >= 0; --i) {
    switch(selects.attributes[i].agg){
      case COUNT: {
        os << std::to_string(tupleset.size()); // 未考虑 NULL 的情况
      }
      break;
      case MAX: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          os << selects.attributes[i].attribute_name;
          break;
        }
        if(0 == strcmp("*", selects.attributes[i].attribute_name)) {
          LOG_ERROR("Invalid Input.");
          return RC::GENERIC_ERROR;
        }
        size_t value_index = 0;
        for (std::vector<TupleField>::const_iterator iter = tupleset.schema().fields().begin(); iter != tupleset.schema().fields().end(); ++iter, ++value_index) {
          if (0 == strcmp((*iter).field_name(), selects.attributes[i].attribute_name)) {
            break;
          }
        }
        size_t sz = tupleset.size(), ans = 0;
        for (size_t j = 1; j < sz; ++j) {
          if (tupleset.tuples()[j].values()[value_index].get()->compare(*(tupleset.tuples()[ans].values()[value_index].get())) > 0) {
            ans = j;
          }
        }
        tupleset.tuples()[ans].values()[value_index].get()->to_string(os);
      }
      break;
      case MIN: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          os << selects.attributes[i].attribute_name;
          break;
        }
        if(0 == strcmp("*", selects.attributes[i].attribute_name)) {
          LOG_ERROR("Invalid Input.");
          return RC::GENERIC_ERROR;
        }
        size_t value_index = 0;
        for (std::vector<TupleField>::const_iterator iter = tupleset.schema().fields().begin(); iter != tupleset.schema().fields().end(); ++iter, ++value_index) {
          if (0 == strcmp((*iter).field_name(), selects.attributes[i].attribute_name)) {
            break;
          }
        }
        size_t sz = tupleset.size(), ans = 0;
        for (size_t j = 1; j < sz; ++j) {
          if (tupleset.tuples()[j].values()[value_index].get()->compare(*(tupleset.tuples()[ans].values()[value_index].get())) < 0) {
            ans = j;
          }
        }
        tupleset.tuples()[ans].values()[value_index].get()->to_string(os);
      }
      break;
      case AVG: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          os << selects.attributes[i].attribute_name;
          break;
        }
        if(0 == strcmp("*", selects.attributes[i].attribute_name)) {
          LOG_ERROR("Invalid Input.");
          return RC::GENERIC_ERROR;
        }
        size_t value_index = 0;
        for (std::vector<TupleField>::const_iterator iter = tupleset.schema().fields().begin(); iter != tupleset.schema().fields().end(); ++iter, ++value_index) {
          if (0 == strcmp((*iter).field_name(), selects.attributes[i].attribute_name)) {
            break;
          }
        }
        size_t sz = tupleset.size();
        float ans = 0;
        for (size_t j = 0; j < sz; ++j) {
          ans += tupleset.tuples()[j].values()[value_index].get()->get_();
        }
        os << (float)(ans / (1.0 * sz));
      }
      break;
      default:{
        LOG_ERROR("Invalid Input.");
        return RC::GENERIC_ERROR;
      }
      break;
    }
    if (i != 0) os << " | "; else os << std::endl;
  }
  LOG_INFO("Do aggr func end.");
  return RC::SUCCESS;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;

  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (int i = selects.relation_num - 1; i >= 0 ; --i) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  tuple_sets_.clear();
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets_.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (selects.attributes[0].agg != NO_AGOP) {
    rc = do_aggregation_func_select(tuple_sets_.front(), selects, ss);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("Failed to do aggregation function select.");
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
  }else 
  if (tuple_sets_.size() > 1) {
    // 本次查询了多张表，需要做join操作
    rc = multi_tables_select_init(trx, session, selects, db, multi_tables_tuple_set);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("Failed to initialize multi tables select.");
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    if(tuple_sets_.size() != total_table) {
      LOG_ERROR("Repetitive tables exist. Please check your input. Tuple sets size = %d, total table num = %d.", tuple_sets_.size(), total_table);
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return RC::GENERIC_ERROR;
    }
    // tuple_sets.front().print(ss);
    // do_multi_tables_select_DFS_tuple.clear();
    do_multi_tables_select_DFS(0, multi_tables_tuple_set);
    LOG_INFO("DFS end.");
    multi_tables_tuple_set.print(ss, true);
  } else {
    // 当前只查询一张表，直接返回结果即可
    tuple_sets_.front().print(ss, false);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (selects.relation_num > 1) {
    TupleSchema::from_table(table, schema);
  }else 
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name) || (attr.attribute_name[0] >= '0' && attr.attribute_name[0] <= '9')) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        // break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}
