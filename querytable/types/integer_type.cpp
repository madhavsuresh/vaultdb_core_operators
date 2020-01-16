//
// Created by madhav on 1/15/20.
//

#include "integer_type.h"

namespace vaultdb::types {
#define INT_CMP(OP)                                                            \
  do {                                                                         \
    switch (left.type_) {                                                      \
    case TypeId::INTEGER32: {                                                  \
      return std::make_unique<BoolResult>(                                     \
          left.value_.int32_val OP right.value_.int32_val);                    \
    }                                                                          \
    case TypeId::INTEGER64: {                                                  \
      return std::make_unique<BoolResult>(                                     \
          left.value_.int64_val OP right.value_.int64_val);                    \
      break;                                                                   \
    }                                                                          \
    default:                                                                   \
      throw;                                                                   \
    }                                                                          \
  } while (0)

std::unique_ptr<BoolResult> vaultdb::types::IntegerType::CompareEquals(
    const vaultdb::types::Value &left,
    const vaultdb::types::Value &right) const {
  INT_CMP(==);
}
std::unique_ptr<BoolResult> vaultdb::types::IntegerType::CompareNotEquals(
    const vaultdb::types::Value &left,
    const vaultdb::types::Value &right) const {
  INT_CMP(!=);
}
} // namespace vaultdb::types
