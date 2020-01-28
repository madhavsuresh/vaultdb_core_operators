//
// Created by madhav on 1/17/20.
//

#include "expression.h"
vaultdb::expression::Expression::Expression(
    vaultdb::types::Value *v1, vaultdb::expression::ExpressionId id) {
  switch (id) {
  case vaultdb::expression::ExpressionId::EQUAL :{
      vaultdb::types::Type::GetInstance(v1->GetType())->CompareEquals(v1, v2);
  }
  default:
    throw;
  }
}

vaultdb::expression::Expression::Expression(
        types::Value *v1, types::Value *v2, ExpressionId id) {
    values_.push_back(v1);
    values_.push_back(v2);
    id_ = id;
}

vaultdb::types::Value execute() {

}
