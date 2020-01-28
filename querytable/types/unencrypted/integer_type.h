//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_INTEGER_TYPE_H
#define TESTING_INTEGER_TYPE_H

#pragma once
#include "querytable/types/value.h"
#include "querytable/types/type.h"
namespace vaultdb::types {

class IntegerType : public Type {
public:
  IntegerType();

  [[nodiscard]] std::unique_ptr<Value>
  CompareEquals(const vaultdb::types::Value &left, const Value &right) const override;

  [[nodiscard]] std::unique_ptr<Value>
  CompareNotEquals(const Value &left, const Value &right) const override;
};
} // namespace vaultdb::types

#endif // TESTING_INTEGER_TYPE_H
