//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERY_SCHEMA_H
#define TESTING_QUERY_SCHEMA_H

#include "query_field_desc.h"
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class QuerySchema {
private:
  std::map<int, std::unique_ptr<QueryFieldDesc>> fields;
  int num_fields;
  size_t length_of_tuple;

public:
  [[nodiscard]] int get_num_fields() const;

  std::map<std::string, int> nameToIndex;

  void put_field(int, QueryFieldDesc &fd);

  size_t get_tuple_len();

  size_t get_field_offset(int field_num) const;

  explicit QuerySchema(int num_fields);

  QuerySchema(QuerySchema &s);

  [[nodiscard]] QueryFieldDesc *get_field(int i) const;
};

#endif // TESTING_QUERY_SCHEMA_H
