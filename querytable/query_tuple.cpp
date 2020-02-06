//
// Created by madhav on 1/13/20.
//

#include "query_tuple.h"
#include <querytable/expression/expression.h>

using namespace vaultdb;

const QueryField *QueryTuple::GetField(int ordinal) const {
  return &this->fields_4[ordinal];
}

void QueryTuple::PutField(int ordinal, std::unique_ptr<QueryField> f) {
  if (ordinal >= 10) {
    throw;
  }
  fields_4[ordinal].SetValue(f->GetValue());
}

void QueryTuple::PutField(int ordinal, const QueryField *f) {
  if (ordinal >= 10) {
    throw;
  }
  fields_4[ordinal].SetValue(f->GetValue());
  //fields_3[ordinal] = new QueryField(*f);
}

void QueryTuple::SetDummyFlag(vaultdb::types::Value *v) {
  vaultdb::expression::Expression ex(v, &dummy_flag_2,
                                     vaultdb::expression::ExpressionId::AND);
  auto result = ex.execute();
  dummy_flag_2.SetValue(&result);
}
void QueryTuple::InitDummy() {
  if (is_encrypted_) {
    dummy_flag_2.SetValue(types::TypeId::ENCRYPTED_BOOLEAN, emp::Bit(false));
  } else {
    dummy_flag_2.SetValue(types::TypeId::BOOLEAN, false);
  }
}
