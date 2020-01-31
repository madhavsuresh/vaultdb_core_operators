//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_ENCRYPTED_INTEGER_TYPE_H
#define TESTING_ENCRYPTED_INTEGER_TYPE_H

#include "querytable/types/type.h"
#include "querytable/types/unencrypted/integer_type.h"
#include <memory>

namespace vaultdb::types {
class EncryptedIntegerType : public Type {
public:
  [[nodiscard]] std::unique_ptr<Value>
  CompareEquals(const Value &left, const Value &right) const override;
  [[nodiscard]] std::unique_ptr<Value>
  CompareNotEquals(const Value &left, const Value &right) const override;
};

} // namespace vaultdb::types

#endif // TESTING_ENCRYPTED_INTEGER_TYPE_H
