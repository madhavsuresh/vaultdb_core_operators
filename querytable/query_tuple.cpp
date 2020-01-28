//
// Created by madhav on 1/13/20.
//

#include "query_tuple.h"

using namespace vaultdb;

const QueryField *QueryTuple::GetField(int ordinal) const {
  return this->fields_.at(ordinal).get();
}


void QueryTuple::PutField(int ordinal, std::unique_ptr<QueryField> f) {
  fields_.emplace(ordinal, std::move(f));
}
void QueryTuple::PutField(int ordinal, const QueryField &f) {
  fields_.emplace(ordinal, std::make_unique<QueryField>(f));
}

bool QueryTuple::IsEqual(const QueryField &f) const {
}


QueryTuple::QueryTuple() {}
