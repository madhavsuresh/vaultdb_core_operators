//
// Created by madhav on 1/17/20.
//

#ifndef TESTING_EXPRESSION_H
#define TESTING_EXPRESSION_H

#include "expression_id.h"
#include <querytable/types/value.h>
namespace vaultdb::expression {
class Expression {

public:
  Expression(types::Value *v1, ExpressionId id);
  Expression(types::Value *v1, types::Value *v2, ExpressionId id);
  Expression(types::Value *v1, types::Value *v2, types::Value *v3,
             ExpressionId id);

  // EvaluateSingle(types::Value v, Op);

  std::unique_ptr<types::Value> execute();

private:
  int num_values_;
  std::vector<types::Value *> values_;
  ExpressionId id_;
  types::Value EvaluateUnary(types::Value *v1, ExpressionId id);
  std::unique_ptr<types::Value> EvaluateBinary(types::Value *v1, types::Value *v2,
                              ExpressionId id);
  types::Value EvaluateTrinary(types::Value *v1, types::Value *v2,
                               types::Value *v3, ExpressionId id);
};
} // namespace vaultdb::expression

#endif // TESTING_EXPRESSION_H
