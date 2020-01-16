//
// Created by madhav on 1/13/20.
//

#include "query_field.h"
using namespace vaultdb;

std::vector<bool> QueryField::get_as_bits() const {
  std::vector<bool> bits;
  switch (type) {
  case INTEGER32:
    for (unsigned int i = 0; i < sizeof(int32_t); i++) {
      bool b;
      unsigned int one = 0x1;
      b = (one << i) & (uint32_t)this->unencrypted_value.int32Value;
      bits.push_back(b);
    }
    break;
  case INTEGER64:
    for (unsigned int i = 0; i < sizeof(int64_t); i++) {
      bool b;
      unsigned int one = 0x1;
      b = (one << i) & (uint64_t)this->unencrypted_value.int64Value;
      bits.push_back(b);
    }
    break;
  default:
    throw;
  }
  return bits;
}

QueryField::QueryField(const QueryField &qf)
    : field_num(qf.field_num), type(qf.type), is_string(qf.is_string),
      bit_length(qf.bit_length), is_encrypted_(qf.is_encrypted_),
      unencrypted_value(qf.unencrypted_value) {
  for (auto &b : qf.base_data) {
    base_data.emplace_back(std::make_unique<emp::Bit>(b->bit));
  }
}

QueryField::QueryField(int64_t val, int fn)
    : is_string(false), type(FieldType::INTEGER64), field_num(fn) {
  value_ =
      std::make_unique<vaultdb::types::Value>(types::TypeId::INTEGER64, val);
}

QueryField::QueryField(int32_t val, int fn)
    : is_string(false), type(FieldType::INTEGER32), field_num(fn) {
  unencrypted_value.int32Value = val;
}

QueryField::QueryField(double val, int fn)
    : is_string(false), type(FieldType::DOUBLE), field_num(fn) {
  unencrypted_value.doubleValue = val;
}

QueryField::QueryField(std::string val, int fn)
    : is_string(true), type(FieldType::VARCHAR), field_num(fn) {
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
