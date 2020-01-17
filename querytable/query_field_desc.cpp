//
// Created by madhav on 1/13/20.
//

#include "query_field_desc.h"

int QueryFieldDesc::GetColumnNumber() const {
  return QueryFieldDesc::column_number;
}

bool QueryFieldDesc::GetIsPrivate() const {
  return QueryFieldDesc::is_private;
}

const std::string &QueryFieldDesc::GetName() const {
  return QueryFieldDesc::name;
}

FieldType QueryFieldDesc::GetType() const { return QueryFieldDesc::type; }
const std::string &QueryFieldDesc::GetTableName() const {
  return QueryFieldDesc::table_name;
}
