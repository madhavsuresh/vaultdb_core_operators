//
// Created by madhav on 1/13/20.
//

#include "QueryTuple.h"

const QueryField *QueryTuple::get_field(int ordinal) const {
    return this->fields.at(ordinal).get();
}

const QueryField* QueryTuple::get_field(string name) const {
}

void QueryTuple::put_field(int ordinal, QueryField &f) {
    fields.emplace(ordinal, std::make_unique<QueryField>(f));
}

QueryTuple::QueryTuple(){

}
