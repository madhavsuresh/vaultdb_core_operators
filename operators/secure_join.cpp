//
// Created by madhav on 1/6/20.
//

#include "secure_join.h"
#include "data/UnsecureTable.h"
#include "emp-tool/emp-tool.h"
#include <querytable/expression/expression.h>
#include <querytable/query_table.h>

Schema schema_merge(SecureTable *t1, SecureTable *t2, SecureTable *newTable,
                    const JoinDef &def) {
  Schema s(0);
  return s;
}

std::unique_ptr<emp::Bit> equality(std::vector<emp::Bit *> r1,
                                   std::vector<emp::Bit *> r2) {
  if (r1.size() != r2.size()) {
    auto b = std::make_unique<emp::Bit>(false, emp::ALICE);
    return b;
  }
  emp::Bit b(true);
  for (int offset = 0; offset < r1.size(); offset++) {
    b = b & (*r1[offset] == *r2[offset]);
  }
  std::cout << std::endl;
  return make_unique<emp::Bit>(b.bit);
}

std::unique_ptr<emp::Bit> RunJoinEqualityCondition(SecureTable *left,
                                                   SecureTable *right,
                                                   int left_idx, int right_idx,
                                                   const JoinDef &def) {
  auto left_bits = left->get_field_range(left_idx, def.left_index);
  auto right_bits = right->get_field_range(right_idx, def.right_index);
  auto eq = equality(left_bits, right_bits);
  std::cout << "Left: " << left_idx << "; Right:" << right_idx << "|"
            << eq->reveal<bool>(emp::PUBLIC) << std::endl;
  return eq;
}

SecureTable EmpJoin(SecureTable *left, SecureTable *right, const JoinDef &def) {
  // TODO(madhavsuresh): simple nested loop join
  for (int l_tup_idx = 0; l_tup_idx < left->get_num_tuples(); l_tup_idx++) {
    for (int r_tup_idx = 0; r_tup_idx < right->get_num_tuples(); r_tup_idx++) {
      auto eq =
          RunJoinEqualityCondition(left, right, l_tup_idx, r_tup_idx, def);
    }
  }
  SecureTable t;
}

unique_ptr<vaultdb::QueryTuple>
MergeTuples(std::vector<vaultdb::QueryTuple *> &tuples,
            const ProjectList &def) {
  unique_ptr<vaultdb::QueryTuple> output = make_unique<vaultdb::QueryTuple>();
  for (auto &p : def.pl) {
    auto f = tuples[p.in_table_index]->GetField(p.in_field_index);
    output->PutField(p.out_field_index, *f);
  }
  return output;
}

unique_ptr<QuerySchema> MergeSchema(std::vector<QuerySchema *> &schemas,
                                    const ProjectList &def) {
  unique_ptr<QuerySchema> output = make_unique<QuerySchema>(def.pl.size());
  for (auto &p : def.pl) {
    output->PutField(p.out_field_index,
                     *schemas.at(p.in_table_index)->GetField(p.in_field_index));
  }
  return output;
}

unique_ptr<QueryTable> Join(QueryTable *left, QueryTable *right,
                            const JoinDef &def) {
  auto qt = make_unique<QueryTable>();
  for (auto &lt : *left) {
      for (auto &rt : *right) {
          expression::Expression ex(lt.GetField(def.left_index)->GetValue(),
                                    rt.GetField(def.right_index)->GetValue(),
                                    def.id);

          auto output = ex.execute();
      }
  }
  return qt;
}
