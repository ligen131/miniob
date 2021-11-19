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
size_t tuple_filter[MAX_NUM][MAX_NUM];
int DFS_tree[MAX_NUM];
TupleSet multi_tables_tuple_set;
bool multi_tables_filter(int cmp_result, CompOp comp_op_) {
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
    case COMP_IS_NOT:
    
    case COMP_IS:


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
    size_t now = 1;
    while (now <= multi_tables_tuple_set.schema().fields().size()){
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
            if(tuple_filter[i][j] == now) {
              tuple.add((*iter));
              ++now;
            }
          }
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
      int left_is_null = tuple_sets_[num].tuples()[DFS_tree[num]].values()[f].get()->_is_null_();
      int right_is_null = (*iter).values()[t].get()->_is_null_();
      if (left_is_null || right_is_null) {
        switch (Multi_tables_compop_[now][i]) {
          case EQUAL_TO:
          case LESS_EQUAL:
          case NOT_EQUAL:
          case LESS_THAN:
          case GREAT_EQUAL:
          case GREAT_THAN:
            ok_ = 0;
          break;
          case COMP_IS_NOT: {
            if (left_is_null && right_is_null) {
              ok_ = 0;
            }
            ok_ = 1;
          }
          case COMP_IS: {
            if (left_is_null && right_is_null) {
              ok_ = 1;
            }
            ok_ = 0;
          }
          default:
          break;
        }
      } else 
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


static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema, AggregationOp agg) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name(), agg);
  return RC::SUCCESS;
}

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
  int tuple_filter_index = 0;
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
        TupleSchema::from_table(table, schema, selects.attributes[0].agg);
        for (int j = 1; j < table->table_meta().field_num(); ++j) {
          tuple_filter[total_table - 1][j - 1] = ++tuple_filter_index;
        }
      }
    }
  }

  int num;
  if(!(selects.attr_num == 1 && strcmp("*", selects.attributes[0].attribute_name) == 0)) {
    for (size_t i = 0; i < selects.attr_num; i++) {
      const RelAttr &attr = selects.attributes[i];
      Table * table = DefaultHandler::get_default().find_table(db,selects.attributes[i].relation_name);
      num = Table_Map[table];
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema, attr.agg);
        int sz = table->table_meta().field_num();
        for (int j = 1; j < sz; ++j) {
          tuple_filter[num - 1][j - 1] = ++tuple_filter_index;
        }
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        rc = schema_add_field(table, attr.attribute_name, schema, attr.agg);
        tuple_filter[num - 1][table->real_table_meta().get_index_by_field(attr.attribute_name) - 1] = ++tuple_filter_index;
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

RC do_aggregation_func_select(TupleSet &tupleset, const Selects &selects, TupleSet &ans_tupleset) {
  LOG_INFO("Start to do aggr func.");

  // 输出表头
  // ans_tupleset.set_schema(tupleset.schema());
  TupleSchema schema;
  ans_tupleset.set_multi_table(false);
  for (size_t i = 0;i < selects.attr_num ; ++i) {
    switch(selects.attributes[i].agg){
      case COUNT:{
        schema.add(FLOATS, selects.relations[0], selects.attributes[i].attribute_name, COUNT);
        // os << "count(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case MAX:{
        schema.add(FLOATS, selects.relations[0], selects.attributes[i].attribute_name, MAX);
        // os << "max(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case MIN:{
        schema.add(FLOATS, selects.relations[0], selects.attributes[i].attribute_name, MIN);
        // os << "min(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      case AVG:{
        schema.add(FLOATS, selects.relations[0], selects.attributes[i].attribute_name, AVG);
        // os << "avg(" << selects.attributes[i].attribute_name << ")";
      }
      break;
      default:{
        LOG_ERROR("Invalid Input.");
        return RC::GENERIC_ERROR;
      }
      break;
    }
    // if (i != selects.attr_num - 1) os << " | "; else os << std::endl;
  }
  ans_tupleset.set_schema(schema);
  
  // 输出结果
  Tuple tuple;
  for (size_t i = 0;i < selects.attr_num ; ++i) {
    switch(selects.attributes[i].agg){
      case COUNT: {
        // os << std::to_string(tupleset.size()); // 未考虑 NULL 的情况
        size_t sz = tupleset.size(), ans = 0;
        if (0 == strcmp("*", selects.attributes[i].attribute_name) ||
            (selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9')) {
          for (size_t j = 0; j < sz; ++j) {
            size_t value_index = 0;
            bool _is_all_null_ = 1;
            for (std::vector<TupleField>::const_iterator iter = tupleset.schema().fields().begin(); iter != tupleset.schema().fields().end(); ++iter, ++value_index) {
              if (!(tupleset.tuples()[j].values()[value_index].get()->_is_null_())) {
                _is_all_null_ = 0;
                break;
              }
            }
            if (!_is_all_null_) {
              ++ans;
            }
          }
          // os << ans;
          tuple.add((float)(ans));
        } else {
          size_t value_index = 0;
          for (std::vector<TupleField>::const_iterator iter = tupleset.schema().fields().begin(); iter != tupleset.schema().fields().end(); ++iter, ++value_index) {
            if (0 == strcmp((*iter).field_name(), selects.attributes[i].attribute_name)) {
              break;
            }
          }
          size_t sz = tupleset.size(), ans = 0;
          for (size_t j = 0; j < sz; ++j) {
            if (!(tupleset.tuples()[j].values()[value_index].get()->_is_null_())) {
              ++ans;
            }
          }
          // os << ans;
          tuple.add((float)(ans));
        }
      }
      break;
      case MAX: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          tuple.add((float)(atof(selects.attributes[i].attribute_name)));
          // os << selects.attributes[i].attribute_name;
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
        while (ans < sz && tupleset.tuples()[ans].values()[value_index].get()->_is_null_()) ++ans;
        if (ans >= sz) {
          tuple.add(__NULL_DATA__, strlen(__NULL_DATA__));
          // os << "NULL";
          break;
        }
        for (size_t j = ans + 1; j < sz; ++j) {
          if (tupleset.tuples()[j].values()[value_index].get()->_is_null_()) continue;
          if (tupleset.tuples()[j].values()[value_index].get()->compare(*(tupleset.tuples()[ans].values()[value_index].get())) > 0) {
            ans = j;
          }
        }
        // tupleset.tuples()[ans].values()[value_index].get()->to_string(os);
        tuple.add((tupleset.tuples()[ans].values()[value_index]));
      }
      break;
      case MIN: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          tuple.add((float)(atof(selects.attributes[i].attribute_name)));
          // os << selects.attributes[i].attribute_name;
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
        while (ans < sz && tupleset.tuples()[ans].values()[value_index].get()->_is_null_()) ++ans;
        if (ans >= sz) {
          tuple.add(__NULL_DATA__, strlen(__NULL_DATA__));
          // os << "NULL";
          break;
        }
        for (size_t j = ans + 1; j < sz; ++j) {
          if (tupleset.tuples()[j].values()[value_index].get()->_is_null_()) continue;
          if (tupleset.tuples()[j].values()[value_index].get()->compare(*(tupleset.tuples()[ans].values()[value_index].get())) < 0) {
            ans = j;
          }
        }
        // tupleset.tuples()[ans].values()[value_index].get()->to_string(os);
        tuple.add((tupleset.tuples()[ans].values()[value_index]));
      }
      break;
      case AVG: {
        if(selects.attributes[i].attribute_name[0] >= '0' && selects.attributes[i].attribute_name[0] <= '9'){
          tuple.add((float)(atof(selects.attributes[i].attribute_name)));
          // os << selects.attributes[i].attribute_name;
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
        size_t sz = tupleset.size(), cnt = 0;
        float ans = 0;
        for (size_t j = 0; j < sz; ++j) {
          if (tupleset.tuples()[j].values()[value_index].get()->_is_null_()) continue;
          ++cnt;
          ans += tupleset.tuples()[j].values()[value_index].get()->get_();
        }
        if (0 == cnt) {
          // os << "NULL";
          tuple.add(__NULL_DATA__, strlen(__NULL_DATA__));
          break;
        }
        // os << (float)(ans / (1.0 * cnt));
        tuple.add((float)(ans / (1.0 * cnt)));
      }
      break;
      default:{
        LOG_ERROR("Invalid Input.");
        return RC::GENERIC_ERROR;
      }
      break;
    }
    // if (i != selects.attr_num - 1) os << " | "; else os << std::endl;
  }
  ans_tupleset.add(std::move(tuple));
  LOG_INFO("Do aggr func end.");
  return RC::SUCCESS;
}

int group_by_index[MAX_NUM], group_by_count[220][MAX_NUM];
RC do_select_group_by(TupleSet &tupleset, const Selects &selects) {
  LOG_INFO("Begin to do group.");
  bool _had_agg = 0;
  for (size_t i = 0; i < selects.attr_num; ++i) {
    if (selects.attributes[i].agg != NO_AGOP) {
      if (AGG_INVALID == selects.attributes[i].agg){
        LOG_ERROR("Agg func invalid.");
        return RC::GENERIC_ERROR;
      }
      _had_agg = 1;
      // break;
    }
  }
  if (selects.group_num == 0 && _had_agg == 0) return RC::SUCCESS;

  TupleSet _base_tupleset = std::move(tupleset);
  tupleset.clear();
  const TupleSchema &_schema = _base_tupleset.schema();
  tupleset.set_schema(_schema);

  for (size_t i = 0; i < selects.group_num; ++i) {
    group_by_index[i] = -1;
    int index = 0;
    for (std::vector<TupleField>::const_iterator iter = _schema.fields().begin(); iter != _schema.fields().end(); ++iter, ++index) {
      if ((selects.groups[i].relation_name == nullptr || strcmp(selects.groups[i].relation_name, (*iter).table_name()) == 0) &&
           strcmp(selects.groups[i].attribute_name, (*iter).field_name()) == 0) {
        group_by_index[i] = index;
        break;
      }
    }
    if(group_by_index[i] == -1){
      LOG_ERROR("Group by input invalid.");
      return RC::GENERIC_ERROR;
    }
  }

  for (std::vector<Tuple>::const_iterator iter = _base_tupleset.tuples().begin(); iter != _base_tupleset.tuples().end(); ++iter) {
    int _ok = -1, index = 0;
    for (std::vector<Tuple>::const_iterator jter = tupleset.tuples().begin(); jter != tupleset.tuples().end(); ++jter, ++index) {
      bool __ok = 0;
      for (size_t i = 0; i < selects.group_num; ++i) {
        if((*iter).values()[group_by_index[i]].get()->compare(*((*jter).values()[group_by_index[i]].get())) != 0) {
          __ok = 0;
          break;
        } else __ok = 1;
      }
      if (__ok) {
        _ok = index;
        break;
      }
    }
    
    Tuple tuple;
    if (_ok != -1) {
      for (size_t i = 0, index = 0; i < selects.attr_num; ++i, ++index) {
        switch (selects.attributes[i].agg) {
          case NO_AGOP: {
            tuple.add((*iter).values()[index]);
          }
          break;
          case MAX: {
            int result = (*iter).values()[index].get()->compare(*(tupleset.tuples()[_ok].values()[index].get()));
            if (result > 0) {
              tuple.add((*iter).values()[index]);
            } else {
              tuple.add(tupleset.tuples()[_ok].values()[index]);
            }
          }
          break;
          case MIN: {
            int result = (*iter).values()[index].get()->compare(*(tupleset.tuples()[_ok].values()[index].get()));
            if (result < 0) {
              tuple.add((*iter).values()[index]);
            } else {
              tuple.add(tupleset.tuples()[_ok].values()[index]);
            }
          }
          break;
          case COUNT: {
            tuple.add(tupleset.tuples()[_ok].values()[index].get()->get_() + 1);
          }
          break;
          case AVG: {
            tuple.add(tupleset.tuples()[_ok].values()[index].get()->get_() + (*iter).values()[index].get()->get_());
            group_by_count[_ok][index]++;
          }
          break;
          default: {

          }
          break;
        }
      }
      tupleset.replace_tuple(_ok, tuple);
    } else {
      for (size_t i = 0, index = 0; i < selects.attr_num; ++i, ++index) {
        if (selects.attributes[i].agg == COUNT) {
          tuple.add(1);
        } else {
          tuple.add((*iter).values()[index]);
        }
        if (selects.attributes[i].agg == AVG) {
          group_by_count[tupleset.size()][index] = 1;
        }
      }
      tupleset.add(std::move(tuple));
    }
  }
  int ind = 0;
  for (std::vector<Tuple>::const_iterator iter = tupleset.tuples().begin(); iter != tupleset.tuples().end(); ++iter, ++ind) {
    Tuple tuple;
    for (size_t i = 0, index = 0; i < selects.attr_num; ++i, ++index) {
      if (selects.attributes[i].agg == AVG) {
        tuple.add(((*iter).values()[index].get()->get_()) / (float)(1.000 * group_by_count[ind][index]));
      } else {
        tuple.add((*iter).values()[index]);
      }
    }
    tupleset.replace_tuple(ind, tuple);
  }
  LOG_INFO("End of group.");
  return RC::SUCCESS;
}

RC do_sub_select(const char *db, Trx *trx, Session *session, const Selects &selects, TupleSet &ans_tupleset) {
  LOG_INFO("Begin to do SUB_select.");
  RC rc = RC::SUCCESS;

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
  
  // std::stringstream ss;
  if (selects.attributes[0].agg != NO_AGOP) {
    rc = do_aggregation_func_select(tuple_sets_.front(), selects, ans_tupleset);
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
    rc = multi_tables_tuple_set._sort(selects);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Fail to do order.");
      return rc;
    }
    rc = do_select_group_by(multi_tables_tuple_set, selects);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Fail to do group.");
      return rc;
    }
    multi_tables_tuple_set.set_multi_table(true);
    ans_tupleset = std::move(multi_tables_tuple_set);
    // multi_tables_tuple_set.print(ss, true);
  } else {
    // 当前只查询一张表，直接返回结果即可
    rc = tuple_sets_.front()._sort(selects);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Fail to do order.");
      return rc;
    }
    rc = do_select_group_by(tuple_sets_.front(), selects);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Fail to do group.");
      return rc;
    }
    tuple_sets_.front().set_multi_table(false);
    ans_tupleset = std::move(tuple_sets_.front());
    // tuple_sets_.front().print(ss, false);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  return RC::SUCCESS;
}

RC do_sub_select_filter(const char *db, Trx *trx, Session *session, int i, const Selects &selects, TupleSet &sub_ans_tupleset, TupleSet &ans_tupleset) {
  RC rc = RC::SUCCESS;
  if (sub_ans_tupleset.schema().fields().size() != 1) {
    LOG_ERROR("Invalid input.");
    end_trx_if_need(session, trx, true);
    return RC::GENERIC_ERROR;
  }
  Selects select_for_father = selects;
  switch (selects.conditions[i].comp) {
    case EQUAL_TO:
    case LESS_EQUAL:
    case NOT_EQUAL:
    case LESS_THAN:
    case GREAT_EQUAL:
    case GREAT_THAN: {
      if (sub_ans_tupleset.tuples().size() > 1) {
        LOG_ERROR("Invalid input.");
        end_trx_if_need(session, trx, true);
        return RC::GENERIC_ERROR;
      }
      if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
        select_for_father.conditions[i].right_value.type = UNDEFINED;
        select_for_father.conditions[i].right_value._is_null = true;
        select_for_father.conditions[i].right_value.data = strdup(__NULL_DATA__);
      } else {
        select_for_father.conditions[i].right_value.type = sub_ans_tupleset.tuples()[0].values().front().get()->get_type();
        sub_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[i].right_value.data);
      }
      rc = do_sub_select(db, trx, session, select_for_father, ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do father select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
    }
    break;
    case COMP_IN: {
      select_for_father.conditions[i].comp = EQUAL_TO;
      size_t tuple_sz = sub_ans_tupleset.tuples().size();
      if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
        select_for_father.conditions[i].right_value.type = UNDEFINED;
        select_for_father.conditions[i].right_value._is_null = true;
        select_for_father.conditions[i].right_value.data = strdup(__NULL_DATA__);
        rc = do_sub_select(db, trx, session, select_for_father, ans_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do father select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }
      } else 
      for (size_t j = 0; j < tuple_sz; ++j) {
        TupleSet one_condition_tupleset;
        select_for_father.conditions[i].right_value.type = sub_ans_tupleset.tuples()[j].values().front().get()->get_type();
        sub_ans_tupleset.tuples()[j].values().front().get()->_get_(select_for_father.conditions[i].right_value.data);
        rc = do_sub_select(db, trx, session, select_for_father, one_condition_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do father select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }
        if (j == 0) {
          ans_tupleset.set_schema(one_condition_tupleset.schema());
          ans_tupleset.set_multi_table((bool)(selects.relation_num > 1));
        }
        size_t sz = one_condition_tupleset.tuples().size();
        for (size_t k = 0; k < sz; ++k) {
          Tuple tuple;
          for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = one_condition_tupleset.tuples()[k].values().begin();
                iter != one_condition_tupleset.tuples()[k].values().end(); ++iter) {
            tuple.add((*iter));
          }
          ans_tupleset.add(std::move(tuple));
        }
      }
    }
    break;
    case COMP_NOT_IN: {
      size_t tuple_sz = sub_ans_tupleset.tuples().size();
      if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
        select_for_father.conditions[i].comp = COMP_IS_NOT;
        select_for_father.conditions[i].right_value.type = UNDEFINED;
        select_for_father.conditions[i].right_value._is_null = true;
        select_for_father.conditions[i].right_value.data = strdup(__NULL_DATA__);
        rc = do_sub_select(db, trx, session, select_for_father, ans_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do father select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }
      } else {
        select_for_father.conditions[i].comp = NOT_EQUAL;
        select_for_father.conditions[i].right_value.type = sub_ans_tupleset.tuples()[0].values().front().get()->get_type();
        sub_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[i].right_value.data);
        for (size_t j = 1; j < tuple_sz; ++j) {
          select_for_father.conditions[select_for_father.condition_num] = select_for_father.conditions[i];
          select_for_father.conditions[select_for_father.condition_num].right_value.data = nullptr;
          sub_ans_tupleset.tuples()[j].values().front().get()->_get_(select_for_father.conditions[select_for_father.condition_num].right_value.data);
          ++select_for_father.condition_num;
        }
        rc = do_sub_select(db, trx, session, select_for_father, ans_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do father select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }
      }
    }
    break;

    case COMP_IS_NOT: 
    case COMP_IS: 
    default:
    break;
  }
  return RC::SUCCESS;
}

CompOp Exchange_CompOp(CompOp comp) {
  switch (comp) {
    case LESS_EQUAL: 
      return GREAT_EQUAL;
    case LESS_THAN:
      return GREAT_THAN;
    case GREAT_EQUAL:
      return LESS_EQUAL;
    case GREAT_THAN:
      return LESS_THAN;
    default:
    break;
  }
  return comp;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {
  LOG_INFO("Begin to do select.");

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection[0];

  std::stringstream ss;
  TupleSet ans_tupleset;
  if (selects.is_sub_query_exist == 1) {
    TupleSet sub_ans_tupleset;
    const Selects &sub_selects = sql->sstr.selection[1];
    if (sub_selects.conditions[0].right_is_attr && strcmp(sub_selects.conditions[0].right_attr.relation_name, selects.relations[0]) == 0) {
      Selects select_for_father = selects;
      select_for_father.condition_num = 0;
      TupleSet father_all_tupleset;
      rc = do_sub_select(db, trx, session, select_for_father, father_all_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do all father select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
      size_t father_all_tp_sz = father_all_tupleset.tuples().size();
      size_t sc_index = 0;
      for (std::vector<TupleField>::const_iterator iter = father_all_tupleset.schema().fields().begin(); 
            iter !=father_all_tupleset.schema().fields().end(); ++iter, ++sc_index) {
        if (strcmp((*iter).field_name(), sub_selects.conditions[0].right_attr.attribute_name) == 0) break;
      }
      size_t left_sc_index = 0;
      for (std::vector<TupleField>::const_iterator iter = father_all_tupleset.schema().fields().begin(); 
            iter !=father_all_tupleset.schema().fields().end(); ++iter, ++left_sc_index) {
        if (strcmp((*iter).field_name(), selects.conditions[0].left_attr.attribute_name) == 0) break;
      }
      ans_tupleset.set_schema(father_all_tupleset.schema());
      Selects select_for_sub = sub_selects;
      select_for_sub.conditions[0].right_is_attr = 0;
      select_for_sub.conditions[0].right_value.type = father_all_tupleset.schema().fields()[sc_index].type();
      for (size_t i = 0; i < father_all_tp_sz; ++i) {
        TupleSet one_condition_tupleset;
        father_all_tupleset.tuples()[i].values()[sc_index].get()->_get_(select_for_sub.conditions[0].right_value.data);
        rc = do_sub_select(db, trx, session, select_for_sub, one_condition_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do sub select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }

        if (one_condition_tupleset.schema().fields().size() != 1) {
          LOG_ERROR("Invalid input.");
          end_trx_if_need(session, trx, true);
          return RC::GENERIC_ERROR;
        }
        if (one_condition_tupleset.tuples().size() > 1) {
          LOG_ERROR("Invalid input.");
          end_trx_if_need(session, trx, true);
          return RC::GENERIC_ERROR;
        }
        if (one_condition_tupleset.tuples().size() == 0 || one_condition_tupleset.tuples()[0].values()[0].get()->_is_null_()) {
          continue;
        }

        bool _ok = 0;
        int cmp_result = father_all_tupleset.tuples()[i].values()[left_sc_index].get()->compare(*(one_condition_tupleset.tuples()[0].values()[0].get()));
        switch (selects.conditions[0].comp) {
          case EQUAL_TO: {
            if (cmp_result == 0) _ok = 1;
          }
          break;
          case LESS_EQUAL: {
            if (cmp_result <= 0) _ok = 1;
          }
          break;
          case NOT_EQUAL: {
            if (cmp_result != 0) _ok = 1;
          }
          break;
          case LESS_THAN: {
            if (cmp_result < 0) _ok = 1;
          }
          break;
          case GREAT_EQUAL: {
            if (cmp_result >= 0) _ok = 1;
          }
          break;
          case GREAT_THAN:  {
            if (cmp_result > 0) _ok = 1;
          }
          break;

          default:
          break;
        }
        if (_ok) {
          Tuple tuple;
          for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = father_all_tupleset.tuples()[i].values().begin();
                iter != father_all_tupleset.tuples()[i].values().end(); ++iter) {
            tuple.add((*iter));
          }
          ans_tupleset.add(std::move(tuple));
        }
      }
    } else {
      rc = do_sub_select(db, trx, session, sub_selects, sub_ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do sub select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
      for (size_t i = 0; i < selects.condition_num; ++i) {
        if (selects.conditions[i].right_is_sub_query) {
          rc = do_sub_select_filter(db, trx, session, i, selects, sub_ans_tupleset, ans_tupleset);
          if (rc != RC::SUCCESS) return rc;
        }
      }
    }
  } else if (selects.is_sub_query_exist == 2) {
    TupleSet sub_ans_tupleset, sub2_ans_tupleset;
    const Selects &sub_selects = sql->sstr.selection[1], &sub2_selects = sql->sstr.selection[2];

    rc = do_sub_select(db, trx, session, sub_selects, sub_ans_tupleset);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Do sub select failed.");
      end_trx_if_need(session, trx, true);
      return rc;
    }
    if (sub_ans_tupleset.schema().fields().size() != 1) {
      LOG_ERROR("Invalid input.");
      end_trx_if_need(session, trx, true);
      return RC::GENERIC_ERROR;
    }

    rc = do_sub_select(db, trx, session, sub2_selects, sub2_ans_tupleset);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Do sub2 select failed.");
      end_trx_if_need(session, trx, true);
      return rc;
    }
    if (sub2_ans_tupleset.schema().fields().size() != 1) {
      LOG_ERROR("Invalid input.");
      end_trx_if_need(session, trx, true);
      return RC::GENERIC_ERROR;
    }

    if (selects.conditions[0].left_is_sub_query) {
      Selects select_for_father = selects;
      if (sub_ans_tupleset.tuples().size() > 1) {
        LOG_ERROR("Invalid input.");
        end_trx_if_need(session, trx, true);
        return RC::GENERIC_ERROR;
      }
      if (sub2_ans_tupleset.tuples().size() > 1) {
        LOG_ERROR("Invalid input.");
        end_trx_if_need(session, trx, true);
        return RC::GENERIC_ERROR;
      }
      if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
        select_for_father.conditions[0].left_value.type = UNDEFINED;
        select_for_father.conditions[0].left_value._is_null = true;
        select_for_father.conditions[0].left_value.data = strdup(__NULL_DATA__);
      } else {
        select_for_father.conditions[0].left_value.type = sub_ans_tupleset.tuples()[0].values().front().get()->get_type();
        sub_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[0].left_value.data);
      }
      if (sub2_ans_tupleset.tuples().size() == 0 || sub2_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
        select_for_father.conditions[0].right_value.type = UNDEFINED;
        select_for_father.conditions[0].right_value._is_null = true;
        select_for_father.conditions[0].right_value.data = strdup(__NULL_DATA__);
      } else {
        select_for_father.conditions[0].right_value.type = sub2_ans_tupleset.tuples()[0].values().front().get()->get_type();
        sub2_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[0].right_value.data);
      }
      rc = do_sub_select(db, trx, session, select_for_father, ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do father select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
    } else {
      Selects select_for_father = selects;
      if (select_for_father.conditions[0].comp == COMP_IN) {
        Condition _swap_cd_ = select_for_father.conditions[1];
        select_for_father.conditions[1] = select_for_father.conditions[0];
        select_for_father.conditions[0] = _swap_cd_;
        TupleSet _swap_tupleset_ = std::move(sub_ans_tupleset);
        sub_ans_tupleset = std::move(sub2_ans_tupleset);
        sub2_ans_tupleset = std::move(_swap_tupleset_);
      }
      switch (select_for_father.conditions[0].comp) {
        case EQUAL_TO:
        case LESS_EQUAL:
        case NOT_EQUAL:
        case LESS_THAN:
        case GREAT_EQUAL:
        case GREAT_THAN: {
          if (sub_ans_tupleset.tuples().size() > 1) {
            LOG_ERROR("Invalid input in sub 1.");
            end_trx_if_need(session, trx, true);
            return RC::GENERIC_ERROR;
          }
          if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
            select_for_father.conditions[0].right_value.type = UNDEFINED;
            select_for_father.conditions[0].right_value._is_null = true;
            select_for_father.conditions[0].right_value.data = strdup(__NULL_DATA__);
          } else {
            select_for_father.conditions[0].right_value.type = sub_ans_tupleset.tuples()[0].values().front().get()->get_type();
            sub_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[0].right_value.data);
          }
        }
        break;
        case COMP_NOT_IN: {
          size_t tuple_sz = sub_ans_tupleset.tuples().size();
          if (sub_ans_tupleset.tuples().size() == 0 || sub_ans_tupleset.tuples()[0].values().front().get()->_is_null_()) {
            select_for_father.conditions[0].comp = COMP_IS_NOT;
            select_for_father.conditions[0].right_value.type = UNDEFINED;
            select_for_father.conditions[0].right_value._is_null = true;
            select_for_father.conditions[0].right_value.data = strdup(__NULL_DATA__);
          } else {
            select_for_father.conditions[0].comp = NOT_EQUAL;
            select_for_father.conditions[0].right_value.type = sub_ans_tupleset.tuples()[0].values().front().get()->get_type();
            sub_ans_tupleset.tuples()[0].values().front().get()->_get_(select_for_father.conditions[0].right_value.data);
            for (size_t j = 1; j < tuple_sz; ++j) {
              select_for_father.conditions[select_for_father.condition_num] = select_for_father.conditions[0];
              select_for_father.conditions[select_for_father.condition_num].right_value.data = nullptr;
              sub_ans_tupleset.tuples()[j].values().front().get()->_get_(select_for_father.conditions[select_for_father.condition_num].right_value.data);
              ++select_for_father.condition_num;
            }
          }
        }
        break;

        default:
        break;
      }
      rc = do_sub_select_filter(db, trx, session, 1, select_for_father, sub2_ans_tupleset, ans_tupleset);
      if (rc != RC::SUCCESS) return rc;
    }
    
  } else if (selects.is_sub_query_exist > 2) {
    
    TupleSet sub_ans_tupleset, sub_sub_ans_tupleset;
    Selects sub_selects = sql->sstr.selection[1], sub_sub_selects = sql->sstr.selection[2];
    if (sub_sub_selects.conditions[0].left_is_attr && 0 != strcmp(sub_sub_selects.conditions[0].left_attr.relation_name, sub_sub_selects.relations[0])) {
      RelAttr _swap_attr = sub_sub_selects.conditions[0].left_attr;
      int _swap_is_attr_ = sub_sub_selects.conditions[0].left_is_attr;
      Value _swap_value_ = sub_sub_selects.conditions[0].left_value;
      sub_sub_selects.conditions[0].left_attr = sub_sub_selects.conditions[0].right_attr;
      sub_sub_selects.conditions[0].left_is_attr = sub_sub_selects.conditions[0].right_is_attr;
      sub_sub_selects.conditions[0].left_value = sub_sub_selects.conditions[0].right_value;
      sub_sub_selects.conditions[0].right_attr = _swap_attr;
      sub_sub_selects.conditions[0].right_is_attr = _swap_is_attr_;
      sub_sub_selects.conditions[0].right_value = _swap_value_;
      sub_sub_selects.conditions[0].comp = Exchange_CompOp(sub_sub_selects.conditions[0].comp);
    }
    if (sub_sub_selects.conditions[0].right_is_attr && strcmp(sub_sub_selects.conditions[0].right_attr.relation_name, selects.relations[0]) == 0) {
      Selects select_for_father = selects;
      select_for_father.condition_num = 0;
      TupleSet father_all_tupleset;
      rc = do_sub_select(db, trx, session, select_for_father, father_all_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do all father select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
      size_t father_all_tp_sz = father_all_tupleset.tuples().size();
      size_t sc_index = 0;
      for (std::vector<TupleField>::const_iterator iter = father_all_tupleset.schema().fields().begin(); 
            iter !=father_all_tupleset.schema().fields().end(); ++iter, ++sc_index) {
        if (strcmp((*iter).field_name(), sub_sub_selects.conditions[0].right_attr.attribute_name) == 0) break;
      }
      size_t left_sc_index = 0;
      for (std::vector<TupleField>::const_iterator iter = father_all_tupleset.schema().fields().begin(); 
            iter !=father_all_tupleset.schema().fields().end(); ++iter, ++left_sc_index) {
        if (strcmp((*iter).field_name(), selects.conditions[0].left_attr.attribute_name) == 0) break;
      }
      ans_tupleset.set_schema(father_all_tupleset.schema());
      Selects select_for_sub_sub = sub_sub_selects;
      select_for_sub_sub.conditions[0].right_is_attr = 0;
      select_for_sub_sub.conditions[0].right_value.type = father_all_tupleset.schema().fields()[sc_index].type();
      for (size_t i = 0; i < father_all_tp_sz; ++i) {
        TupleSet one_condition_tupleset;
        father_all_tupleset.tuples()[i].values()[sc_index].get()->_get_(select_for_sub_sub.conditions[0].right_value.data);
        rc = do_sub_select(db, trx, session, select_for_sub_sub, one_condition_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do sub sub select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }

        if (one_condition_tupleset.schema().fields().size() != 1) {
          LOG_ERROR("Invalid input.");
          end_trx_if_need(session, trx, true);
          return RC::GENERIC_ERROR;
        }

        // if (one_condition_tupleset.tuples().size() == 0 ) {
        //   continue;
        // }

        Selects select_for_sub = sub_selects;
        // select_for_sub.conditions[0].right_value.type = one_condition_tupleset.tuples()[0].values()[0].get()->get_type();
        // one_condition_tupleset.tuples()[0].values()[0].get()->_get_(select_for_sub.conditions[0].right_value.data);
        TupleSet one_sub_condition_tupleset;
        rc = do_sub_select_filter(db, trx, session, 0, select_for_sub, one_condition_tupleset, one_sub_condition_tupleset);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Do sub select failed.");
          end_trx_if_need(session, trx, true);
          return rc;
        }

        bool _ok = 0, __ok = 1;
        switch (selects.conditions[0].comp) {
          case EQUAL_TO:
          case LESS_EQUAL:
          case NOT_EQUAL:
          case LESS_THAN:
          case GREAT_EQUAL:
          case GREAT_THAN: {
            if (one_sub_condition_tupleset.tuples().size() != 1 || one_sub_condition_tupleset.tuples()[0].values()[0].get()->_is_null_()) {
              __ok = 0;
              break;
            }
          }
          break;
          case COMP_IN: {
            if (one_sub_condition_tupleset.tuples().size() == 0 || one_sub_condition_tupleset.tuples()[0].values()[0].get()->_is_null_()) {
              __ok = 0;
              break;
            }
          }
          break;
          case COMP_NOT_IN: {
            if (one_sub_condition_tupleset.tuples().size() == 0 || one_sub_condition_tupleset.tuples()[0].values()[0].get()->_is_null_()) {
              _ok = 1;
              break;
            }
          }
          break;

          default:
          break;
        }
        if (!__ok) continue;
        if (!_ok) {
          int cmp_result = father_all_tupleset.tuples()[i].values()[left_sc_index].get()->compare(*(one_sub_condition_tupleset.tuples()[0].values()[0].get()));
          switch (selects.conditions[0].comp) {
            case EQUAL_TO: {
              if (cmp_result == 0) _ok = 1;
            }
            break;
            case LESS_EQUAL: {
              if (cmp_result <= 0) _ok = 1;
            }
            break;
            case NOT_EQUAL: {
              if (cmp_result != 0) _ok = 1;
            }
            break;
            case LESS_THAN: {
              if (cmp_result < 0) _ok = 1;
            }
            break;
            case GREAT_EQUAL: {
              if (cmp_result >= 0) _ok = 1;
            }
            break;
            case GREAT_THAN:  {
              if (cmp_result > 0) _ok = 1;
            }
            break;
            case COMP_IN: {
              size_t one_sub_condition_tupleset_sz = one_sub_condition_tupleset.tuples().size();
              for (size_t j = 0; j < one_sub_condition_tupleset_sz; ++j) {
                if (0 == father_all_tupleset.tuples()[i].values()[left_sc_index].get()->compare(*(one_sub_condition_tupleset.tuples()[j].values()[0].get()))) {
                  _ok = 1;
                  break;
                }
              }
            }
            break;
            case COMP_NOT_IN: {
              _ok = 1;
              size_t one_sub_condition_tupleset_sz = one_sub_condition_tupleset.tuples().size();
              for (size_t j = 0; j < one_sub_condition_tupleset_sz; ++j) {
                if (0 == father_all_tupleset.tuples()[i].values()[left_sc_index].get()->compare(*(one_sub_condition_tupleset.tuples()[j].values()[0].get()))) {
                  _ok = 0;
                  break;
                }
              }
            }
            break;

            default:
            break;
          }
        }
        if (_ok) {
          Tuple tuple;
          for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = father_all_tupleset.tuples()[i].values().begin();
                iter != father_all_tupleset.tuples()[i].values().end(); ++iter) {
            tuple.add((*iter));
          }
          ans_tupleset.add(std::move(tuple));
        }
      }
    } else {
      rc = do_sub_select(db, trx, session, sub_sub_selects, sub_sub_ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do sub_sub select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }

      rc = do_sub_select_filter(db, trx, session, 0, sub_selects, sub_sub_ans_tupleset, sub_ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do sub select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }

      rc = do_sub_select_filter(db, trx, session, 0, selects, sub_ans_tupleset, ans_tupleset);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Do sub select failed.");
        end_trx_if_need(session, trx, true);
        return rc;
      }
    }
  } else if (selects.is_sub_query_exist == 0){
    rc = do_sub_select(db, trx, session, selects, ans_tupleset);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Do single select failed.");
      end_trx_if_need(session, trx, true);
      return rc;
    }
  }
  ans_tupleset.print(ss);

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
    TupleSchema::from_table(table, schema, NO_AGOP);
  }else 
  for (size_t i = 0; i < selects.attr_num; i++) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name) || (attr.attribute_name[0] >= '0' && attr.attribute_name[0] <= '9')) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema, attr.agg);
        // break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema, attr.agg);
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
