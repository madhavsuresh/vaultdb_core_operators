//
// Created by madhav on 1/29/20.
//

#include "common/defs.h"
#include "query_table.h"

struct ShareCount {
  EmpParty party;
  int num_tuples;
};

struct ShareDef {
  std::map<EmpParty, ShareCount> share_map;
};

std::unique_ptr<QueryTable> share_data(QuerySchema *shared_schema,
                                       EmpParty party,
                                       const QueryTable *input_table,
                                       ShareDef def) {

  std::unique_ptr<QueryTable> output_table = std::make_unique<QueryTable>();
  // TODO(madhavsuresh): copy the schema over to the new table. need to make
  // copy
  // constructor for QuerySchema.

  std::unique_ptr<emp::Batcher> batcherAlice = std::make_unique<emp::Batcher>();
  for (int i = 0; i < def.share_map[EmpParty::ALICE].num_tuples; i++) {
    for (int j = 0; j < shared_schema->GetNumFields(); j++) {
      switch (shared_schema->GetField(j)->GetType()) {
      case INTEGER64: {
        int64_t val =
            input_table->GetTuple(i)->GetField(j)->GetValue()->GetInt64();
        batcherAlice->add<emp::Integer>(64, party == EmpParty::ALICE ? val : 0);
        break;
      }
      default:
        throw;
      }
    }
  }

  std::unique_ptr<emp::Batcher> batcherBob = std::make_unique<emp::Batcher>();
  for (int i = 0; i < def.share_map[EmpParty::BOB].num_tuples; i++) {
    for (int j = 0; j < shared_schema->GetNumFields(); j++) {
      switch (shared_schema->GetField(j)->GetType()) {
      case INTEGER64: {
        auto val =
            input_table->GetTuple(i)->GetField(j)->GetValue()->GetInt64();
        batcherBob->add<emp::Integer>(64, party == EmpParty::BOB ?: 0);
        break;
      }
      default:
        throw;
      }
    }
  }
  batcherAlice->make_semi_honest(static_cast<int>(EmpParty::ALICE));
  batcherBob->make_semi_honest(static_cast<int>(EmpParty::BOB));

}