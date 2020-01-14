//
// Created by madhav on 1/13/20.
//

#include "QueryFieldDesc.h"

int QueryFieldDesc::get_column_number() const {
    return QueryFieldDesc::column_number;
}

bool QueryFieldDesc::get_is_private() const {
    return QueryFieldDesc::is_private;
}

const std::string &QueryFieldDesc::get_name() const {
    return QueryFieldDesc::name;
}

FieldType QueryFieldDesc::get_type() const {
    return QueryFieldDesc::type;
}
const std::string &QueryFieldDesc::get_table_name() const {
    return QueryFieldDesc::table_name;
}
