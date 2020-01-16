//
// Created by madhav on 1/15/20.
//

#include <common/macros.h>
#include "encrypted_integer_type.h"
namespace vaultdb::types {
#define EMP_INT_CMP(OP)                                                        \
  do {                                                                         \
    emp::Bit b = left.value_.emp_integer_ OP right.value_.emp_integer_;          \
    std::unique_ptr<BoolResult> res = std::make_unique<BoolResult>(b);         \
    return res;                                                                \
  } while (0)

std::unique_ptr<BoolResult>
EncryptedIntegerType::CompareEquals(const Value &left,
                                    const Value &right) const {
  EMP_INT_CMP(==);
}
std::unique_ptr<BoolResult>
EncryptedIntegerType::CompareNotEquals(const Value &left,
                                       const Value &right) const {
  EMP_INT_CMP(!=);
}
} // namespace vaultdb::types