//
// Created by madhav on 2/5/20.
//

#ifndef TESTING_ENCRYPTED_BOOLEAN_TYPE_H
#define TESTING_ENCRYPTED_BOOLEAN_TYPE_H

#include <querytable/types/type.h>
namespace vaultdb::types {
class EncryptedBooleanType : public Type {

public:
  static EncryptedBooleanType &shared_instance() {
    static EncryptedBooleanType type;
    return type;
  }
  [[nodiscard]] std::unique_ptr<Value>
  CompareEquals(const Value &left, const Value &right) const override;
  [[nodiscard]] std::unique_ptr<Value>
  CompareNotEquals(const Value &left, const Value &right) const override;
  [[nodiscard]] std::unique_ptr<Value> And(const Value &left,
                                           const Value &right) const override;
};
} // namespace vaultdb::types

#endif // TESTING_ENCRYPTED_BOOLEAN_TYPE_H
