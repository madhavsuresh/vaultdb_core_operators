//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_VALUE_H
#define TESTING_VALUE_H
#include "emp-tool/emp-tool.h"
#include "type_id.h"
#include <cstdint>
#include <memory>

namespace vaultdb::types {
class Value {

public:
  friend class Type;
  friend class ArithmeticType;
  friend class EncryptedIntegerType;
  friend class IntegerType;
protected:
  const bool is_encrypted_;
  const TypeId type_;
  union unencrypted_val {
    int8_t bool_val;
    int64_t int64_val;
    int32_t int32_val;
    int32_t date_val;
    double double_val;
    char *varchar_val;
    std::unique_ptr<emp::Bit> emp_bit;
    std::unique_ptr<emp::Integer> emp_integer;
    std::unique_ptr<emp::Float32> emp_float32;
    std::unique_ptr<emp::Float> emp_float;
    std::unique_ptr<std::vector<emp::Bit>> emp_bit_array;
  } const value_;

  const int64_t len_;
};
} // namespace vaultdb::types

#endif // TESTING_VALUE_H
