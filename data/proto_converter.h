//
// Created by madhav on 12/28/19.
//

#ifndef TESTING_PROTO_CONVERTER_H
#define TESTING_PROTO_CONVERTER_H

#include "UnsecureTable.h"
#include <dbquery.pb.h>
#include <querytable/query_table.h>

std::unique_ptr<Schema> proto_to_schema(const dbquery::Schema &proto_schema);
std::unique_ptr<UnsecureTable> proto_to_unsecuretable(dbquery::Table t);
std::unique_ptr<QueryTable> proto_to_querytable(const dbquery::Table &t);
#endif // TESTING_PROTO_CONVERTER_H
