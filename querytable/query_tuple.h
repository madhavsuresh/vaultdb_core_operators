//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERY_TUPLE_H
#define TESTING_QUERY_TUPLE_H

#include "dummy_flag.h"
#include "query_field.h"
#include <map>
#include <memory>
#include <vector>

namespace vaultdb {
class QueryTuple {
private:
  std::map<int, std::unique_ptr<const QueryField>> fields_;
  DummyFlag flag_;

public:
  QueryTuple(QueryTuple &t);

  QueryTuple();

  const vaultdb::QueryField *get_field(int ordinal) const;
  const vaultdb::QueryField &get_field(string name) const;
  void put_field(int ordinal, const vaultdb::QueryField &f);
  [[nodiscard]] bool is_equal(const QueryField &f) const;
  void set_dummy_flag(emp::Bit &flag);
  void set_dummy_flag(bool flag);

  /* Iterator Utilities */
  typedef typename std::map<
      int, std::unique_ptr<const vaultdb::QueryField>>::iterator iterator;
  typedef typename std::map<int, std::unique_ptr<const vaultdb::QueryField>>::
      const_iterator const_iterator;
  iterator begin() { return fields_.begin(); }
  const_iterator begin() const { return fields_.begin(); }
  const_iterator cbegin() const { return fields_.cbegin(); }
  iterator end() { return fields_.end(); }
  const_iterator end() const { return fields_.end(); }
  const_iterator cend() const { return fields_.cend(); }
};

} // namespace vaultdb
#endif // TESTING_QUERY_TUPLE_H
