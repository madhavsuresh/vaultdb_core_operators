//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERY_FIELD_DESC_H
#define TESTING_QUERY_FIELD_DESC_H

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

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

private:
  const int column_number;
  const bool is_private;
  const std::string name;
  const FieldType type;
  // origin table name
  const std::string table_name;

public:
  [[nodiscard]] int get_column_number() const;

  [[nodiscard]] bool get_is_private() const;

  [[nodiscard]] const std::string &get_name() const;

  [[nodiscard]] FieldType get_type() const;

  [[nodiscard]] const std::string &get_table_name() const;

  [[nodiscard]] size_t get_field_size() const;

  QueryFieldDesc(QueryFieldDesc &f)
      : column_number(f.column_number), is_private(f.is_private), name(f.name),
        type(f.type), table_name(f.table_name){};

  QueryFieldDesc(QueryFieldDesc &f, int col_num)
      : column_number(col_num), is_private(f.is_private), name(f.name),
        type(f.type), table_name(f.table_name){};
  QueryFieldDesc(int col_num, bool is_priv, const std::string &n, FieldType t,
                 const std::string &tab)
      : column_number(col_num), is_private(is_priv), name(n), type(t),
        table_name(tab){};
};

#endif // TESTING_QUERY_FIELD_DESC_H
