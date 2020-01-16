//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_TYPE_H
#define TESTING_TYPE_H
namespace vaultdb {
namespace types {
enum class TypeId {
  INTEGER32,
  INTEGER64,
  FLOAT32,
  FLOAT64,
  DOUBLE,
  NUMERIC,
  TIMESTAMP,
  TIME,
  DATE,
  VARCHAR
};

} // end namespace types
} // end namespace vaultdb

#endif // TESTING_TYPE_H
