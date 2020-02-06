//
// Created by madhav on 1/15/20.
//

#include "encrypted_integer_type.h"
#include <common/macros.h>
namespace vaultdb::types {
#define EMP_INT_CMP(OP)                                                        \
  do {                                                                         \
    emp::Bit b =                                                               \
        *left.value_.emp_integer_.get() OP * right.value_.emp_integer_.get();  \
    auto res = std::make_unique<Value>(TypeId::ENCRYPTED_BOOLEAN, b);          \
    return res;                                                                \
  } while (0)

#define EMP_INT_BINARY(OP)                                                     \
  do {                                                                         \
    emp::Integer b =                                                           \
        *left.value_.emp_integer_.get() OP * right.value_.emp_integer_.get();  \
    auto res = std::make_unique<Value>(left.type_, b, left.len_);              \
    return res;                                                                \
  } while (0)

std::unique_ptr<Value>
EncryptedIntegerType::CompareEquals(const Value &left,
                                    const Value &right) const {
  EMP_INT_CMP(==);
}
std::unique_ptr<Value>
EncryptedIntegerType::CompareNotEquals(const Value &left,
                                       const Value &right) const {
  EMP_INT_CMP(!=);
}
EncryptedIntegerType::EncryptedIntegerType() {}
std::unique_ptr<Value> EncryptedIntegerType::And(const Value &left,
                                                 const Value &right) const {
  EMP_INT_BINARY(^);
}
} // namespace vaultdb::types
