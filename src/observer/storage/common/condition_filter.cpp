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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"

using namespace common;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type_left, AttrType attr_type_right, CompOp comp_op, bool _is_null_exist)
{
  if ((attr_type_left < CHARS || attr_type_left > TEXTS) && !_is_null_exist) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type_left);
    return RC::INVALID_ARGUMENT;
  }
  if ((attr_type_right < CHARS || attr_type_right > TEXTS) && !_is_null_exist) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type_right);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  attr_type_left_ = attr_type_left;
  attr_type_right_ = attr_type_right;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC Select_Date_Checker(Value values){
  int dates=0;
  if(values.type==DATES){
    dates = *(int*)values.data;
    if(dates==-1)return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}


RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  RC rc = RC::SUCCESS;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;
  bool _is_null_exist = 0;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
  } else {
    rc = Select_Date_Checker(condition.left_value);
    if(rc != RC::SUCCESS){
      LOG_WARN("Date invalid. %s.", table.name());
      return rc;
    }

    left.is_attr = false;
    if (condition.left_value._is_null == 1) {
      left.value = malloc(4);
      memcpy(left.value, __NULL_DATA__, 4);
      _is_null_exist = 1;
    } else {
      left.value = condition.left_value.data;  // 校验type 或者转换类型
    }
    type_left = condition.left_value.type;

    left.attr_length = 0;
    left.attr_offset = 0;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();

    right.value = nullptr;
  } else {
    rc = Select_Date_Checker(condition.right_value);
    if(rc != RC::SUCCESS){
      LOG_WARN("Date invalid. %s.", table.name());
      return rc;
    }

    right.is_attr = false;
    if (condition.right_value._is_null == 1) {
      right.value = malloc(4);
      memcpy(right.value, __NULL_DATA__, 4);
      _is_null_exist = 1;
    } else {
      right.value = condition.right_value.data;  // 校验type 或者转换类型
    }
    type_right = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
  }

  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现
  
  if ((left.value != nullptr && strcmp((char*)left.value, __NULL_DATA__) == 0) || 
      (right.value != nullptr && strcmp((char*)right.value, __NULL_DATA__) == 0)) {
    _is_null_exist = 1;
  }

  bool field_type_compare_compatible_table[TEXTS + 1][TEXTS + 1]={};
  field_type_compare_compatible_table[FLOATS][INTS] = field_type_compare_compatible_table[INTS][FLOATS] = true;

  if (type_left != type_right && !field_type_compare_compatible_table[type_left][type_right] && !_is_null_exist) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }


  return init(left, right, type_left, type_right, condition.comp, _is_null_exist);
}

#define Abs(x) (((x)<0)?(-(x)):(x))

bool DefaultConditionFilter::filter(const Record &rec) const
{
  char *left_value = nullptr;
  char *right_value = nullptr;
  char s[256] = {""};

  if (left_.is_attr) {  // value
    strncpy(s, (char *)(rec.data + left_.attr_offset), left_.attr_length);
    left_value = s;
  } else {
    left_value = (char *)left_.value;
  }

  if (right_.is_attr) {
    strncpy(s, (char *)(rec.data + right_.attr_offset), right_.attr_length);
    right_value = s;
  } else {
    right_value = (char *)right_.value;
  }

  bool left_is_null = (bool)(0 == strcmp(left_value, __NULL_DATA__));
  bool right_is_null = (bool)(0 == strcmp(right_value, __NULL_DATA__));

  if (left_is_null || right_is_null) {
    switch (comp_op_) {
      case EQUAL_TO:
      case LESS_EQUAL:
      case NOT_EQUAL:
      case LESS_THAN:
      case GREAT_EQUAL:
      case GREAT_THAN:
        return false;
      case COMP_IS_NOT: {
        if (left_is_null && right_is_null) {
          return false;
        }
        return true;
      }
      case COMP_IS: {
        if (left_is_null && right_is_null) {
          return true;
        }
        return false;
      }

      default:
        break;
    }

    LOG_PANIC("Never should print this (In NULL).");
    return false;  // should not go here
  }

  int cmp_result = 0;
  float left, right;
  switch (attr_type_left_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      left = (float)(*(int*)(left_value));
    } break;
    case FLOATS: {
      left = *(float *)left_value;
    } break;
    case DATES: {
      int left_ = *(int *)left_value;
      int right_ = *(int *)right_value;
      cmp_result = left_ - right_;
    }break;
    default: {
    }
  }
  switch (attr_type_right_) {
    case CHARS: {  

    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      right = (float)(*(int *)right_value);
      if (Abs(left - right) < (1e-4)) cmp_result = 0;
      else if (left - right < 0) cmp_result = -1;
      else if (left - right > 0) cmp_result = 1;
    } break;
    case FLOATS: {
      right = *(float *)right_value;
      if (Abs(left - right) < (1e-4)) cmp_result = 0;
      else if (left - right < 0) cmp_result = -1;
      else if (left - right > 0) cmp_result = 1;
      // cmp_result = (int)(left - right);
    } break;
    case DATES: {

    }break;
    default: {
    }
  }

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

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
