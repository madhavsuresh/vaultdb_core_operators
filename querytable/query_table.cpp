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
QueryTable::QueryTable() : is_encrypted_(false), num_tuples_(0) {}
QueryTable::QueryTable(int num_tuples)
    : is_encrypted_(false), num_tuples_(num_tuples) {}

QueryTable::QueryTable(bool is_encrypted)
    : is_encrypted_(is_encrypted), num_tuples_(0) {}
QueryTable::QueryTable(bool is_encrypted, int num_tuples)
    : is_encrypted_(is_encrypted), num_tuples_(num_tuples) {}

const bool QueryTable::GetIsEncrypted() const { return is_encrypted_; }
void QueryTable::AllocateQueryTuples() {
  if (num_tuples_ == 0) {
    throw;
  }
}
