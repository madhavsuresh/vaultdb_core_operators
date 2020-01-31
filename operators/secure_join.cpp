//
// Created by madhav on 1/6/20.
//

#include "secure_join.h"
#include "emp-tool/emp-tool.h"
#include <querytable/expression/expression.h>
#include <querytable/query_table.h>

std::unique_ptr<vaultdb::QueryTuple>
MergeTuples(std::vector<vaultdb::QueryTuple *> &tuples,
            const ProjectList &def) {
  std::unique_ptr<vaultdb::QueryTuple> output = std::make_unique<vaultdb::QueryTuple>();
  for (auto &p : def.pl) {
    auto f = tuples[p.in_table_index]->GetField(p.in_field_index);
    output->PutField(p.out_field_index, *f);
  }
  return output;
}

std::unique_ptr<QuerySchema> MergeSchema(std::vector<QuerySchema *> &schemas,
                                    const ProjectList &def) {
  std::unique_ptr<QuerySchema> output = std::make_unique<QuerySchema>(def.pl.size());
  for (auto &p : def.pl) {
    output->PutField(p.out_field_index,
                     *schemas.at(p.in_table_index)->GetField(p.in_field_index));
  }
  return output;
}

std::unique_ptr<QueryTable> Join(QueryTable *left, QueryTable *right,
                            const JoinDef &def) {
  auto qt = std::make_unique<QueryTable>();
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
