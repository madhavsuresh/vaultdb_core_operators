//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_TYPE_H
#define TESTING_TYPE_H
#include "bool_result.h"
#include "type_id.h"
#include "value.h"
#include <memory>

namespace vaultdb::types {

class Type {
public:
  inline static Type *GetInstance(TypeId type_id);

  virtual std::unique_ptr<BoolResult> CompareEquals(const Value &left,
                                                    const Value &right) const;
  virtual std::unique_ptr<BoolResult>
  CompareNotEquals(const Value &left, const Value &right) const;

  friend class ArithmeticType;
  friend class IntegerType;
  friend class EncryptedIntegerType;

protected:
  TypeId type_id_;
};

} // namespace vaultdb::types
#endif // TESTING_TYPE_H
