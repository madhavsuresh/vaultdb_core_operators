//
// Created by madhav on 1/13/20.
//

#include "query_field.h"
using namespace vaultdb;

QueryField::QueryField(const QueryField &qf)
    : field_num_(qf.field_num_), type(qf.type), is_string(qf.is_string),
      bit_length(qf.bit_length), is_encrypted_(qf.is_encrypted_),
      unencrypted_value(qf.unencrypted_value) {
  for (auto &b : qf.base_data) {
    base_data.emplace_back(std::make_unique<emp::Bit>(b->bit));
  }
}

QueryField::QueryField(int64_t val, int fn)
    : is_string(false), type(FieldType::INTEGER64), field_num_(fn) {
  value_ =
      std::make_unique<vaultdb::types::Value>(types::TypeId::INTEGER64, val);
}

QueryField::QueryField(int32_t val, int fn)
    : is_string(false), type(FieldType::INTEGER32), field_num_(fn) {
  unencrypted_value.int32Value = val;
}

QueryField::QueryField(double val, int fn)
    : is_string(false), type(FieldType::DOUBLE), field_num_(fn) {
  unencrypted_value.doubleValue = val;
}

QueryField::QueryField(std::string val, int fn)
    : is_string(true), type(FieldType::VARCHAR), field_num_(fn) {
  unsigned int len = val.length() + 1;
  char *tmp = (char *)malloc(len);
  strncpy(tmp, val.c_str(), len);
  tmp[len - 1] = '\0';
  if (val.length() > 128) {
    throw;
  }
  this->unencrypted_value.stringValue = tmp;
  assert(strlen(this->unencrypted_value.stringValue) == (val.length()));
}

types::Value *QueryField::GetValue() const { return value_.get(); }
QueryField::QueryField(emp::Integer val, int length, int field_num)
    : is_string(false), type(FieldType::INTEGER64), field_num_(field_num) {

  value_ = std::make_unique<vaultdb::types::Value>(
      types::TypeId::ENCRYPTED_INTEGER64, val, length);
}
