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

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"
#include "storage/common/table.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name) {
  LOG_INFO("relation attr init %s %s",relation_name, attribute_name);
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->agg = NO_AGOP;
  LOG_INFO("end relation attr init %s %s",relation_name, attribute_name);
}
void relation_attr_init_(RelAttr *relation_attr, const char *relation_name, const char *attribute_name, AggregationOp AggOp) {
  relation_attr_init(relation_attr, relation_name, attribute_name);
  relation_attr->agg = AggOp;
}

void relation_attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  relation_attr->agg = NO_AGOP;
}


void orders_init(OrderBy *order, const char *relation_name, const char *attribute_name, OrderOp orderp) {
  order->orderp = orderp;
  if (relation_name != nullptr) {
    order->relation_name = strdup(relation_name);
  } else {
    order->relation_name = nullptr;
  }
  order->attribute_name = strdup(attribute_name);
}
void orders_destroy(OrderBy *order) {
  free(order->relation_name);
  free(order->attribute_name);
  order->relation_name = nullptr;
  order->attribute_name = nullptr;
}
void groups_init(GroupBy *group, const char *relation_name, const char *attribute_name) {
  if (relation_name != nullptr) {
    group->relation_name = strdup(relation_name);
  } else {
    group->relation_name = nullptr;
  }
  group->attribute_name = strdup(attribute_name);
}
void groups_destroy(GroupBy *group) {
  free(group->relation_name);
  free(group->attribute_name);
  group->relation_name = nullptr;
  group->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v) {
  value->type = INTS;
  // printf("INTEGER %d %d\n",value->type,v);
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v) {
  value->type = CHARS;
  // printf("STRING %d %s %d\n",value->type,v,strlen(v));
  value->data = strdup(v);
}
#define DATE_CHECK_FAILURE ans=-1; \
      value->data = malloc(sizeof(ans)); \
      memcpy(value->data, &ans, sizeof(ans)); \
      return
void value_init_date(Value *value, const char *v) {
  value->type = DATES;
  // printf("DATE %d \"%s\"\n",value->type,v);
  int ans=0,l=strlen(v),y=0,m=0,d=0,nn=1,x;
  for(int i=0;i<l;++i){
    if(v[i]=='-'){
      ++nn;
      if(nn>3){DATE_CHECK_FAILURE;}
    }else if(v[i]>='0'&&v[i]<='9'){
      x=v[i]-'0';
      if(nn==1){
        y=y*10+x;
        if(y>2038){DATE_CHECK_FAILURE;}
      }else if(nn==2){
        m=m*10+x;
        if(m>12){DATE_CHECK_FAILURE;}
      }else{
        d=d*10+x;
        if(d>31){DATE_CHECK_FAILURE;}
      }
      // printf("DATE %d %d %d %d %d %d\n",i,nn,x,y,m,d);
    }else{DATE_CHECK_FAILURE;}
  }
  if(y<1970){DATE_CHECK_FAILURE;}
  if(m<=0){DATE_CHECK_FAILURE;}
  if(d<=0){DATE_CHECK_FAILURE;}
  if(y%4==0&&m==2&&d>29){DATE_CHECK_FAILURE;}
  if(y%4!=0&&m==2&&d>28){DATE_CHECK_FAILURE;}
  if((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&d>31){DATE_CHECK_FAILURE;}
  if((m==4||m==6||m==9||m==11)&&d>30){DATE_CHECK_FAILURE;}
  if(y==2038&&m>2){DATE_CHECK_FAILURE;}
  ans=y*10000+m*100+d;
  // printf("DATE %d %d\n",value->type,ans);
  value->data = malloc(sizeof(ans));
  memcpy(value->data, &ans, sizeof(ans));
}
void value_init_null(Value *value) {
  value->type = UNDEFINED;
  value->_is_null = 1;
}
void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
  value->_is_null = 0;
}

void condition_init(Condition *condition, CompOp comp, 
                    int left_is_attr, RelAttr *left_attr, Value *left_value,
                    int right_is_attr, RelAttr *right_attr, Value *right_value) {
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  } else {
    condition->left_value = *left_value;
  }

  condition->right_is_attr = right_is_attr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else if (right_value == nullptr) {
    condition->right_value.data = nullptr;
    condition->right_value.type = UNDEFINED;
    condition->right_value._is_null = 0;
  } else {
    condition->right_value = *right_value;
  }
  condition->right_is_sub_query = 0;
}
void condition_init_(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
    int right_is_attr, RelAttr *right_attr, Value *right_value, int right_is_sub) {
  condition_init(condition, comp, left_is_attr, left_attr, left_value, right_is_attr, right_attr, right_value);
  condition->right_is_sub_query = right_is_sub;
}
void condition_destroy(Condition *condition) {
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable) {
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->_nullable = nullable;
}
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
  attr_info->_nullable = 0;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr) {
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name) {
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(selects->conditions)/sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void selects_append_orders(Selects *selects, OrderBy *orders) {
  selects->orders[selects->order_num++] = *orders;
}
void selects_append_groups(Selects *selects, GroupBy *groups) {
  selects->groups[selects->group_num++] = *groups;
}

void selects_destroy(Selects *selects) {
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->order_num; i++) {
    orders_destroy(&selects->orders[i]);
  }
  selects->order_num = 0;

  for (size_t i = 0; i < selects->group_num; i++) {
    groups_destroy(&selects->groups[i]);
  }
  selects->group_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num, size_t data_num, int data_list_r[]) {
  assert(value_num <= sizeof(inserts->values)/sizeof(inserts->values[0]));

  inserts->relation_name = strdup(relation_name);
  for (size_t i = 0; i < value_num; i++) {
    inserts->values[i] = values[i];
  }
  inserts->value_num = value_num;

  for (size_t i = 0; i < data_num; i++) {
    inserts->data_list_r[i] = data_list_r[i];
  }
  inserts->data_num = data_num;
}
void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(deletes->conditions)/sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes) {
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name,
                  Value *value, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions)/sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table, const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, 
                       const char *relation_name, const char *attr_name[], size_t attr_num, int _is_unique_) {
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->attr_num = attr_num;
  create_index->_is_unique = _is_unique_;
  for (size_t i = 0; i < attr_num; ++i) {
    create_index->attribute_name[i] = strdup(attr_name[i]);
  }
  
}
void create_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);
  for (size_t i = 0; i < create_index->attr_num; ++i) {
    free(create_index->attribute_name[i]);
    create_index->attribute_name[i] = nullptr;
  }
  create_index->attr_num = 0;

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->_is_unique = false;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query) {
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection[0]);
      selects_destroy(&query->sstr.selection[1]);
      selects_destroy(&query->sstr.selection[2]);
    }
    break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    }
    break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    }
    break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    }
    break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    }
    break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    }
    break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    }
    break;
    case SCF_SYNC: {

    }
    break;
    case SCF_SHOW_TABLES:
    break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    }
    break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    }
    break;
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query  *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}