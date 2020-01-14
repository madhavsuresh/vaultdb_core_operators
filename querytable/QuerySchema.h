//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERYSCHEMA_H
#define TESTING_QUERYSCHEMA_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <variant>
#include "QueryFieldDesc.h"

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


#endif //TESTING_QUERYSCHEMA_H
