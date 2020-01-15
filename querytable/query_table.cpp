//
// Created by madhav on 1/7/20.
//

#include "query_table.h"

void QueryTable::put_tuple(std::unique_ptr<QueryTuple> t) {
  tuples_.push_back(std::move(t));
  std::cout << "wow!";
}

void QueryTable::set_schema(std::unique_ptr<QuerySchema> s) {
  QueryTable::schema_ = std::move(s);
}
