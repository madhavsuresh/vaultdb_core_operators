//
// Created by madhav on 1/7/20.
//

#ifndef TESTING_QUERY_TABLE_H
#define TESTING_QUERY_TABLE_H

#include "emp-tool/emp-tool.h"
#include "query_schema.h"
#include "query_tuple.h"
#include <memory>
using namespace vaultdb;

template <class BaseIterator> class DereferenceIterator : public BaseIterator {
public:
  using value_type = typename BaseIterator::value_type::element_type;
  using pointer = value_type *;
  using reference = value_type &;

  explicit DereferenceIterator(const BaseIterator &other)
      : BaseIterator(other) {}

  reference operator*() const { return *(this->BaseIterator::operator*()); }
  pointer operator->() const { return this->BaseIterator::operator*().get(); }
  reference operator[](size_t n) const {
    return *(this->BaseIterator::operator[](n));
  }
};

template <typename Iterator>
DereferenceIterator<Iterator> dereference_iterator(Iterator t) {
  return DereferenceIterator<Iterator>(t);
}

class QueryTable {
private:
  std::vector<std::unique_ptr<vaultdb::QueryTuple>> tuples_;
  std::unique_ptr<QuerySchema> schema_;

public:
  typedef DereferenceIterator<
      std::vector<std::unique_ptr<vaultdb::QueryTuple>>::iterator>
      iterator;
  typedef DereferenceIterator<
      std::vector<std::unique_ptr<vaultdb::QueryTuple>>::const_iterator>
      const_iterator;
  void set_schema(std::unique_ptr<QuerySchema> s);
  void put_tuple(std::unique_ptr<vaultdb::QueryTuple> t);

  iterator begin() { return dereference_iterator(tuples_.begin()); }
  const_iterator begin() const { return dereference_iterator(tuples_.begin()); }
  const_iterator cbegin() const {
    return dereference_iterator(tuples_.cbegin());
  }
  iterator end() { return dereference_iterator(tuples_.end()); }
  const_iterator end() const { return dereference_iterator(tuples_.end()); }
  const_iterator cend() const { return dereference_iterator(tuples_.cend()); }
};

#endif // TESTING_QUERY_TABLE_H
