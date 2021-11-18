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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <string>
#include <ostream>
#include "common/log/log.h"
#include "storage/common/table.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual float get_() const = 0;
  virtual void _get_(void* &ans) const = 0;
  virtual int _is_null_() const = 0;
  virtual AttrType get_type() const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  float get_() const override {
    return (float)value_;
  }

  void _get_(void* &ans) const override {
    // float value = (float)(value_);
    ans = malloc(sizeof(value_));
    memcpy(ans, &value_, sizeof(value_));
  }

  int _is_null_() const override {
    return 0;
  }

  AttrType get_type() const override {
    return INTS;
  }

private:
  int value_;
};

#include <iomanip>
#include <iostream>
class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << std::setprecision(4);
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  float get_() const override {
    return value_;
  }

  void _get_(void* &ans) const override {
    ans = malloc(sizeof(value_));
    memcpy(ans, &value_, sizeof(value_));
  }

  int _is_null_() const override {
    return 0;
  }

  AttrType get_type() const override {
    return FLOATS;
  }

private:
  float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int Check_is_it_date() const {
    const char *s = value_.c_str();
    size_t len = strlen(s);
    int ans = 0;
    if(len != 10) return 0;
    for (size_t i = 0; i < len; ++i){
      if(i == 5 || i == 8){
        if(s[i] != '-')return 0;
      } else if(s[i] < '0' || s[i] > '9') return 0;
      else ans = ans * 10 + s[i] - '0';
    }
    return ans;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    int d1 = Check_is_it_date(), d2 = string_other.Check_is_it_date();
    if(d1 && d2){
      return d1 - d2;
    }
    LOG_INFO("Compare %s %s",value_.c_str(), string_other.value_.c_str());
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  float get_() const override {
    int d = Check_is_it_date();
    return (float)d;
  }

  void _get_(void* &ans) const override {
    int d = Check_is_it_date();
    if (d != 0) {
      ans = malloc(sizeof(d));
      memcpy(ans, &d, sizeof(d));
    } else {
      ans = strdup(value_.c_str());
    }
  }

  int _is_null_() const override {
    if (0 == strcmp(value_.c_str(), __NULL_DATA__)) {
      return 1;
    }
    return 0;
  }

  AttrType get_type() const override {
    if (Check_is_it_date() != 0) return DATES;
    return CHARS;
  }

private:
  std::string value_;
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
