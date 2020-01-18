//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_ENCRYPTED_INTEGER_TYPE_H
#define TESTING_ENCRYPTED_INTEGER_TYPE_H

#include "querytable/types/arithmetic_type.h"
#include "querytable/types/type.h"
#include "querytable/types/unencrypted/integer_type.h"
#include <memory>

namespace vaultdb::types {
class EncryptedIntegerType : public ArithmeticType {
public:
  [[nodiscard]] std::unique_ptr<BoolResult>
  CompareEquals(const Value &left, const Value &right) const override;
  [[nodiscard]] std::unique_ptr<BoolResult>
  CompareNotEquals(const Value &left, const Value &right) const override;
};
Type *Type::GetInstance(TypeId type_id) {
  switch (type_id) {
  case TypeId::INTEGER32:
  case TypeId::INTEGER64:
    return new IntegerType();
  }
}
} // namespace vaultdb::types

#endif // TESTING_ENCRYPTED_INTEGER_TYPE_H
