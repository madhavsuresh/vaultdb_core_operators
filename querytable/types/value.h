//
// Created by madhav on 1/15/20.
//

#pragma once
#include "emp-tool/emp-tool.h"
#include "type.h"
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
  Value(TypeId type, int32_t val);
  Value(TypeId type, int64_t val);

protected:
  const bool is_encrypted_;
  const TypeId type_;
  const int64_t len_;
  union UnencryptedVal {
    int8_t bool_val;
    int64_t int64_val;
    int32_t int32_val;
    int32_t date_val;
    double double_val;
    char *varchar_val;
  };
  struct value {
    UnencryptedVal unencrypted_val;
    std::unique_ptr<emp::Bit> emp_bit_;
    std::unique_ptr<emp::Integer> emp_integer_;
    std::unique_ptr<emp::Float32> emp_float32_;
    std::unique_ptr<emp::Float> emp_float_;
    std::unique_ptr<std::vector<emp::Bit>> emp_bit_array_;
  } value_;
};
} // namespace vaultdb::types
