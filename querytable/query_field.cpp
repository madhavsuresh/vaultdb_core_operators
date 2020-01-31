//
// Created by madhav on 1/13/20.
//

#include "query_field.h"
using namespace vaultdb;

QueryField::QueryField(const QueryField &qf)
    : field_num_(qf.field_num_) {
  throw;
}

QueryField::QueryField(int64_t val, int fn)
    : field_num_(fn) {
  value_ =
      std::make_unique<vaultdb::types::Value>(types::TypeId::INTEGER64, val);
}

QueryField::QueryField(int32_t val, int fn)
    : field_num_(fn) {
  throw;
}

QueryField::QueryField(double val, int fn)
    : field_num_(fn) {
  throw;
}

QueryField::QueryField(std::string val, int fn)
    : field_num_(fn) {
  unsigned int len = val.length() + 1;
  char *tmp = (char *)malloc(len);
  strncpy(tmp, val.c_str(), len);
  tmp[len - 1] = '\0';
  if (val.length() > 128) {
    throw;
  }
  throw;
}

types::Value *QueryField::GetValue() const { return value_.get(); }

QueryField::QueryField(emp::Integer val, int length, int field_num)
    :  field_num_(field_num) {
  value_ = std::make_unique<vaultdb::types::Value>(
      types::TypeId::ENCRYPTED_INTEGER64, val, length);
}
