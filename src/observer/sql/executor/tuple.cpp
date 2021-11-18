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
// Created by Wangyunlai on 2021/5/14.
//

#include <algorithm>

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema, AggregationOp agg) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name(), agg);
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name, NO_AGOP);
}
void TupleSchema::add(AttrType type, const char *table_name, const char *field_name, AggregationOp agg) {
  fields_.emplace_back(type, table_name, field_name, agg);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name) && 
        NO_AGOP == field.agg()) {
      return;
    }
  }

  add(type, table_name, field_name);
}
void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name, AggregationOp agg) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name) && 
        agg == field.agg()) {
      return;
    }
  }

  add(type, table_name, field_name, agg);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool is_multi_tables) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // // 判断有多张表还是只有一张表
  // std::set<std::string> table_names;
  // for (const auto &field: fields_) {
  //   table_names.insert(field.table_name());
  // }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    switch(iter->agg()) {
      case MAX: {
        os << "max(";
      }
      break;
      case MIN: {
        os << "min(";
      }
      break;
      case COUNT: {
        os << "count(";
      }
      break;
      case AVG: {
        os << "avg(";
      }
      break;
      default: {

      }
      break;
    }
    if (is_multi_tables) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name();
    if(iter->agg() != NO_AGOP) {
      os << ")";
    }
    os << " | ";
  }

  switch(fields_.back().agg()) {
    case MAX: {
      os << "max(";
    }
    break;
    case MIN: {
      os << "min(";
    }
    break;
    case COUNT: {
      os << "count(";
    }
    break;
    case AVG: {
      os << "avg(";
    }
    break;
    default: {

    }
    break;
  }
  if (is_multi_tables) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name();
  if(fields_.back().agg() != NO_AGOP) {
    os << ")";
  }
  os << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

size_t select_order_index[MAX_NUM];
const Selects *_selects_for_order;
bool do_select_order_cmp(const Tuple &a, const Tuple &b) {
  for (size_t i = 0; i < _selects_for_order->order_num; ++i) {
    int result = a.values()[select_order_index[i]].get()->compare(*(b.values()[select_order_index[i]].get()));
    if (result < 0) return _selects_for_order->orders[i].orderp == ORDER_ASC;
    if (result > 0) return _selects_for_order->orders[i].orderp == ORDER_DESC;
  }
  return false;
}

RC TupleSet::_sort(const Selects &selects) {
  if (selects.order_num == 0) return RC::SUCCESS;
  LOG_INFO("Begin prepare for sorting.");
  for (size_t i = 0; i < selects.order_num; ++i) {
    const std::vector<TupleField>&fields = schema_.fields();
    int index = 0;
    bool _ok = 0;
    for (std::vector<TupleField>::const_iterator iter = fields.begin(); iter != fields.end(); ++iter, ++index) {
      if((selects.orders[i].relation_name == nullptr || strcmp((*iter).table_name(), selects.orders[i].relation_name) == 0) && 
          strcmp((*iter).field_name(), selects.orders[i].attribute_name) == 0) {
            select_order_index[i] = index;
            _ok = 1;
            break;
          }
    }
    if (!_ok) {
      LOG_ERROR("Order input invalid.");
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
  _selects_for_order = &selects;
  LOG_INFO("Ready for sorting.");
  sort(tuples_.begin(), tuples_.end(), do_select_order_cmp);
  LOG_INFO("End of sorting.");
  return RC::SUCCESS;
}

void TupleSet::print(std::ostream &os) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, is_multi_tables);

  if (tuples_.size() == 0) return;
  int tuple_index = -1;
  for (const Tuple &item : tuples_) {
    ++tuple_index;
    int values_index = 0;
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter, ++values_index) {
      if (1 == (*iter)->_is_null_()) {
        os << "NULL";
      } else {
        (*iter)->to_string(os);
      }
      os << " | ";
    }
    if (1 == values.back()->_is_null_()) {
      os << "NULL";
    } else {
      values.back()->to_string(os);
    }
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

inline int Min(int a,int b){
  if(a<b) return a;
  return b;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);

    if (strcmp((char*)(record + field_meta->offset()), __NULL_DATA__) == 0) {
      tuple.add(__NULL_DATA__, strlen(__NULL_DATA__));
      continue;
    }

    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        char *s = (char*)(record + field_meta->offset());
        char t[256] = {""};
        // LOG_INFO("%s %d",s,strlen(s));
        strncpy(t, s, Min(strlen(s), field_meta->len()));  // 现在当做Cstring来处理
        // t[Min(strlen(s), field_meta->len())] = 0;
        // LOG_INFO("%s %d",s,strlen(s));
        tuple.add(t, strlen(t));
      }
      break;
      case DATES: {
        int value = *(int*)(record + field_meta->offset());
        std::string ans=std::to_string(value/10000) + "-" ;
        if(value%10000/100<10)ans = ans + '0';
        ans = ans + std::to_string(value%10000/100) + "-" ;
        if(value%100<10)ans = ans + '0';
        ans = ans + std::to_string(value%100);
        const char *s = ans.c_str();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      case TEXTS: {
        int value = *(int*)(record + field_meta->offset());
        char *s = table_->get_text(value);
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


