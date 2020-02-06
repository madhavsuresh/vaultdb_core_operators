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
  vaultdb::types::Value dummy_flag_2;
  bool is_encrypted_{};

public:
  void SetIsEncrypted(bool isEncrypted);

private:
  QueryField fields_4[5];
  int num_fields_{};

public:
  QueryTuple(QueryTuple &t);

  QueryTuple() { dummy_flag_2.SetValue(types::TypeId::BOOLEAN, false); };

  QueryTuple(bool is_encrypted) : is_encrypted_(is_encrypted) {
    if (is_encrypted_) {
      dummy_flag_2.SetValue(types::TypeId::ENCRYPTED_BOOLEAN, emp::Bit(false));
    } else {
      dummy_flag_2.SetValue(types::TypeId::BOOLEAN, false);
    }
  }
  void InitDummy();

  const vaultdb::QueryField *GetField(int ordinal) const;
  const vaultdb::QueryField &GetField(string name) const;
  void PutField(int ordinal, const vaultdb::QueryField &f);
  void PutField(int ordinal, std::unique_ptr<QueryField> f);
  void PutField(int ordinal, const QueryField *f);
  void SetDummyFlag(vaultdb::types::Value *v);
  void SetDummyFlag(emp::Bit &flag);
  void SetDummyFlag(bool flag);
};

} // namespace vaultdb
#endif // TESTING_QUERY_TUPLE_H
