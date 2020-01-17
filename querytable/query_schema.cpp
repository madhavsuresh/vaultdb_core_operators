//
// Created by madhav on 1/13/20.
//

#include "query_schema.h"

QuerySchema::QuerySchema(int num_fields) {}
void QuerySchema::PutField(int index, QueryFieldDesc &fd) {
  QuerySchema::fields.emplace(index,
                              std::make_unique<QueryFieldDesc>(fd, index));
}
