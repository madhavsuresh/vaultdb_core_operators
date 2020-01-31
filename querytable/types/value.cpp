//
// Created by madhav on 1/15/20.
//
#include "value.h"

namespace vaultdb::types {
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
