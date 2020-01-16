//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERY_FIELD_H
#define TESTING_QUERY_FIELD_H

#include "emp-tool/emp-tool.h"
#include "query_field_desc.h"
#include <memory>
#include <vector>

namespace vaultdb::querytable {

enum VaultType { INT32, VARCHAR_ };

class QueryField {
private:
  bool is_encrypted_;
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
  const int field_num;

public:
  QueryField(const QueryField &qf);

  QueryField(int64_t val, int field_num);

  QueryField(int32_t val, int field_num);

  QueryField(double val, int field_num);

  QueryField(char *val, int field_num);

  QueryField(std::string val, int field_num);

  [[nodiscard]] std::vector<bool> get_as_bits() const;

  [[nodiscard]] int64_t to(int64_t) const {
    return this->unencrypted_value.int64Value;
  }

  [[nodiscard]] int32_t to(int32_t) const {
    return this->unencrypted_value.int32Value;
  }

  [[nodiscard]] double to(double) const {
    return this->unencrypted_value.doubleValue;
  }

  emp::Bit *to(emp::Bit *) const {
    if (base_data.size() != 1) {
      throw;
    }
    return base_data[0].get();
  }

  emp::Integer *to(emp::Integer *) const {
    if (empInt == nullptr) {
      throw;
    }
    return empInt.get();
  }

  virtual emp::Bit **to(emp::Bit **) const {};

  template <typename T> T get_as() const {
    T obj;
    return to(obj);
  }
};

class QueryFieldInt32 : public QueryField {
private:
  int32_t val;

public:
  QueryFieldInt32(int32_t val, int fieldNum) : QueryField(val, fieldNum) {}

  emp::Bit **to(emp::Bit **) const { throw; }
};

class QueryFieldInt64 : public QueryField {
private:
  int64_t val{};

public:
  QueryFieldInt64(int64_t val, int fieldNum) : QueryField(val, fieldNum) {}
};
} // namespace vaultdb::querytable
#endif // TESTING_QUERY_FIELD_H
