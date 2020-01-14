//
// Created by madhav on 1/7/20.
//

#include "QueryTable.h"


void QueryTable::put_tuple(std::unique_ptr<QueryTuple> t) {
    tuples_.push_back(std::move(t));
    std::cout << "wow!";
}
