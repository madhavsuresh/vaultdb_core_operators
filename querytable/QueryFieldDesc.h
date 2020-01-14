//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERYFIELDDESC_H
#define TESTING_QUERYFIELDDESC_H


#include <string>
#include <map>
#include <vector>
#include <memory>
#include <variant>

enum FieldType {
    UNSUPPORTED,
    INTEGER32,
    INTEGER64,
    VARCHAR,
    DOUBLE,
    NUMERIC,
    TIMESTAMP,
    TIME,
    BIGINT
};

class QueryFieldDesc {
    QueryFieldDesc();

    int column_number;
    std::string name;
    FieldType type;
    // origin table name
    std::string table_name;
    QueryFieldDesc(QueryFieldDesc &f);
    [[nodiscard]] size_t get_field_size() const;
};


#endif //TESTING_QUERYFIELDDESC_H
