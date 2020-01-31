//
// Created by madhav on 1/15/20.
//

#include <common/macros.h>
#include "encrypted_integer_type.h"
namespace vaultdb::types {
#define EMP_INT_CMP(OP)                                                        \
  do {                                                                         \
    emp::Bit b = left.value_.emp_integer_ OP right.value_.emp_integer_;          \
    auto res = std::make_unique<Value>(TypeId::ENCRYPTED_BOOLEAN,b);         \
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
} // namespace vaultdb::types
