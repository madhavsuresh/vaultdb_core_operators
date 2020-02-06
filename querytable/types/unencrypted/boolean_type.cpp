//
// Created by madhav on 2/5/20.
//

#include "boolean_type.h"
namespace vaultdb::types {
#define BOOL_BINARY(OP)                                                        \
  do {                                                                         \
                                                                               \
    auto res = std::make_unique<Value>(                                        \
        left.type_, left.value_.unencrypted_val.bool_val ^                     \
                        right.value_.unencrypted_val.bool_val);                \
    return res;                                                                \
  } while (0)

std::unique_ptr<Value> vaultdb::types::BooleanType::CompareEquals(
    const vaultdb::types::Value &left,
    const vaultdb::types::Value &right) const {
  BOOL_BINARY(==);
}
std::unique_ptr<Value> vaultdb::types::BooleanType::CompareNotEquals(
    const vaultdb::types::Value &left,
    const vaultdb::types::Value &right) const {
  BOOL_BINARY(!=);
}
std::unique_ptr<Value>
vaultdb::types::BooleanType::And(const vaultdb::types::Value &left,
                                 const vaultdb::types::Value &right) const {
  BOOL_BINARY(^);
}
} // namespace vaultdb::types
