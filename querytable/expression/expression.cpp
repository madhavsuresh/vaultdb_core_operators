//
// Created by madhav on 1/17/20.
//

#include "expression.h"
#include "common/macros.h"
namespace vaultdb::expression {
Expression::Expression(vaultdb::types::Value *v1, ExpressionId id) {
  values_.push_back(v1);
  id_ = id;
}

Expression::Expression(types::Value *v1, types::Value *v2, ExpressionId id) {
  values_.push_back(v1);
  values_.push_back(v2);
  id_ = id;
}

std::unique_ptr<vaultdb::types::Value> Expression::execute() {
  switch (values_.size()) {
  case 1: {
    // return EvaluateUnary(values_[0], id_);
  }
  case 2: {
    return EvaluateBinary(values_[0], values_[1], id_);
  }
  case 3: {
    // return EvaluateTrinary(values_[0], values_[1], values_[3], id_);
  }
  }
}

std::unique_ptr<vaultdb::types::Value>
Expression::EvaluateBinary(types::Value *v1, types::Value *v2,
                           ExpressionId id) {
  VAULTDB_ASSERT(v1->GetType() == v2->GetType());

  switch (id) {

  case ExpressionId::INVALID:
    throw;
  case ExpressionId::LESSTHANOREQUAL:
    throw;
  case ExpressionId::EQUAL:
    return vaultdb::types::Type::GetInstance(v1->GetType())
        .CompareEquals(*v1, *v2);
  case ExpressionId::GREATERTHANOREQUAL:
    throw;
  case ExpressionId::LESSTHAN:
    throw;
  case ExpressionId::GREATERTHAN:
    throw;
  case ExpressionId::SUBSTRING:
    throw;
  }
}
} // namespace vaultdb::expression
