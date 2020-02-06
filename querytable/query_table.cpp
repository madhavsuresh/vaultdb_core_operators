//
// Created by madhav on 1/7/20.
//

#include "query_table.h"

void QueryTable::PutTuple(std::unique_ptr<QueryTuple> t) {
  tuples_.push_back(std::move(t));
}

QueryTuple *QueryTable::GetTuple(int idx) const { return tuples_[idx].get(); }

void QueryTable::SetSchema(std::unique_ptr<QuerySchema> s) {
  QueryTable::schema_ = std::move(s);
}

const QuerySchema *QueryTable::GetSchema() const { return schema_.get(); }

int QueryTable::GetNumTuples() const { return tuples_.size(); }
QueryTable::QueryTable() : is_encrypted_(false) { tuples_.reserve(25000); }
QueryTable::QueryTable(int size) : is_encrypted_(false) {
  tuples_.reserve(size);
}

QueryTable::QueryTable(bool is_encrypted) : is_encrypted_(is_encrypted) {}
const bool QueryTable::GetIsEncrypted() const { return is_encrypted_; }
