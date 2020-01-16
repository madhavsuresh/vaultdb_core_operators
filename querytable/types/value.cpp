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
} // namespace vaultdb::types
