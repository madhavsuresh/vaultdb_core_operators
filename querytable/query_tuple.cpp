//
// Created by madhav on 1/13/20.
//

#include "query_tuple.h"

using namespace vaultdb;

const QueryField *QueryTuple::get_field(int ordinal) const {
  return this->fields_.at(ordinal).get();
}


void QueryTuple::put_field(int ordinal, const QueryField &f) {
  fields_.emplace(ordinal, std::make_unique<QueryField>(f));
}

bool QueryTuple::is_equal(const QueryField &f) const {
}


QueryTuple::QueryTuple() {}
