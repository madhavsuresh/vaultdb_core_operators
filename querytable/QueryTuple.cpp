//
// Created by madhav on 1/13/20.
//

#include "QueryTuple.h"

const QueryField *QueryTuple::get_field(int ordinal) const {
    return this->fields.at(ordinal).get();
}

const QueryField* QueryTuple::get_field(string name) const {
    for (auto &a: *this) {
    }
}
