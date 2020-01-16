//
// Created by madhav on 1/15/20.
//

#ifndef TESTING_TYPE_ID_H
#define TESTING_TYPE_ID_H
namespace vaultdb::types {
enum class TypeId {
  INVALID = 0,
  INTEGER32,
  INTEGER64,
  FLOAT32,
  FLOAT64,
  DOUBLE,
  NUMERIC,
  TIMESTAMP,
  TIME,
  DATE,
  VARCHAR,
  ENCRYPTED_INTEGER32,
  ENCRYPTED_INTEGER64
};

} // namespace vaultdb::types

#endif // TESTING_TYPE_ID_H
