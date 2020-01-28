//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_ARITHMETIC_TYPE_H
#define TESTING_ARITHMETIC_TYPE_H

#include "type.h"
#include "value.h"

namespace vaultdb::types {
class ArithmeticType : public Type {
public:
  virtual std::unique_ptr<Value>
  CompareEquals(const Value &left, const Value &right) const override = 0;
  virtual std::unique_ptr<Value>
  CompareNotEquals(const Value &left, const Value &right) const override = 0;
};
} // namespace vaultdb::types
#endif // TESTING_ARITHMETIC_TYPE_H
