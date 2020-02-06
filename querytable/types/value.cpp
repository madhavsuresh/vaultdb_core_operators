//
// Created by madhav on 1/15/20.
//
#include "value.h"

namespace vaultdb::types {

Value::Value(Value &val)
    : len_(val.len_), type_(val.type_), is_encrypted_(val.is_encrypted_) {
  switch (val.type_) {

  case TypeId::BOOLEAN:
    Value(val.type_, val.value_.unencrypted_val.bool_val);
    break;
  case TypeId::INTEGER32:
    Value(val.type_, val.value_.unencrypted_val.int32_val);
    break;
  case TypeId::INTEGER64:
    Value(val.type_, val.value_.unencrypted_val.int64_val);
    break;
  case TypeId::ENCRYPTED_INTEGER32:
  case TypeId::ENCRYPTED_INTEGER64:
    Value(val.type_, *(val.value_.emp_integer_.get()), val.len_);
    break;
  case TypeId::ENCRYPTED_BOOLEAN:
    Value(val.type_, *(val.value_.emp_bit_.get()));
    break;
  case TypeId::INVALID:
  case TypeId::FLOAT32:
  case TypeId::FLOAT64:
  case TypeId::DOUBLE:
  case TypeId::NUMERIC:
  case TypeId::TIMESTAMP:
  case TypeId::TIME:
  case TypeId::DATE:
  case TypeId::VARCHAR:
    throw;
  }

}

Value::Value(TypeId type, int64_t val)
    : type_(type), len_(sizeof(int64_t)), is_encrypted_(false) {
  value_.unencrypted_val.int64_val = val;
}

Value::Value(TypeId type, int32_t val)
    : type_(type), len_(sizeof(int32_t)), is_encrypted_(false) {
  value_.unencrypted_val.int32_val = val;
}
Value::Value(TypeId type, bool val)
    : type_(type), len_(sizeof(bool)), is_encrypted_(false) {
  value_.unencrypted_val.bool_val = val;
}

Value::Value(TypeId type, emp::Bit val)
    : type_(type), len_(sizeof(bool)), is_encrypted_(true) {
  value_.emp_bit_ = std::make_unique<emp::Bit>(val.bit);
}

Value::Value(TypeId type, const emp::Integer val, int len)
    : type_(type), len_(len), is_encrypted_(true) {
  value_.emp_integer_ = std::make_unique<emp::Integer>(val);
}

TypeId Value::GetType() { return Value::type_; }

int32_t Value::GetInt32() const { return value_.unencrypted_val.int32_val; }
int64_t Value::GetInt64() const { return value_.unencrypted_val.int64_val; }
} // namespace vaultdb::types
