//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERY_FIELD_H
#define TESTING_QUERY_FIELD_H

#include "emp-tool/emp-tool.h"
#include "query_field_desc.h"
#include <memory>
#include <vector>
#include "types/value.h"

namespace vaultdb {


class QueryField {
private:

  const int field_num_;
  std::unique_ptr<types::Value> value_;

public:
  QueryField(const QueryField &qf);

  QueryField(int64_t val, int field_num);

  QueryField(int32_t val, int field_num);

  QueryField(double val, int field_num);

  QueryField(char *val, int field_num);

  QueryField(std::string val, int field_num);

  QueryField(emp::Integer, int length, int field_num);

  [[nodiscard]] types::Value *GetValue() const;
};

} // namespace vaultdb::querytable
#endif // TESTING_QUERY_FIELD_H
