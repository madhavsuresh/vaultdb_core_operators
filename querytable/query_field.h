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
  bool is_encrypted_;

  const int field_num;
  std::unique_ptr<types::Value> value_;
  //TODO(madhavsuresh): Deprecated, removed all below.
  std::vector<std::unique_ptr<emp::Bit>> base_data;
  std::unique_ptr<emp::Integer> empInt;
  int bit_length;
  union val {
    int64_t int64Value;
    int32_t int32Value;
    double doubleValue;
    char *stringValue;
  } unencrypted_value{};
  const bool is_string;
  const FieldType type;

public:
  QueryField(const QueryField &qf);

  QueryField(int64_t val, int field_num);

  QueryField(int32_t val, int field_num);

  QueryField(double val, int field_num);

  QueryField(char *val, int field_num);

  QueryField(std::string val, int field_num);

  [[nodiscard]] types::Value *GetValue() const;
};

} // namespace vaultdb::querytable
#endif // TESTING_QUERY_FIELD_H
