//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_INTEGER_TYPE_H
#define TESTING_INTEGER_TYPE_H

#include "arithmetic_type.h"
#include "value.h"
namespace vaultdb::types {

class IntegerType : public ArithmeticType {
public:
  IntegerType();

  [[nodiscard]] std::unique_ptr<BoolResult>
  CompareEquals(const vaultdb::types::Value &left, const Value &right) const override;

  [[nodiscard]] std::unique_ptr<BoolResult>
  CompareNotEquals(const Value &left, const Value &right) const override;
};
} // namespace vaultdb::types

#endif // TESTING_INTEGER_TYPE_H
