//
// Created by madhav on 1/7/20.
//

#include "query_table.h"

void QueryTable::PutTuple(std::unique_ptr<QueryTuple> t) {
  tuples_.push_back(std::move(t));
}

void QueryTable::SetSchema(std::unique_ptr<QuerySchema> s) {
  QueryTable::schema_ = std::move(s);
}
