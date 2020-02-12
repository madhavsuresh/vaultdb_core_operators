//
// Created by madhav on 1/6/20.
//

#include "secure_join.h"
#include "emp-tool/emp-tool.h"
#include <querytable/expression/expression.h>
#include <querytable/query_table.h>

void MergeTuples(QueryTuple *output, QueryTuple **tuples,
                 const ProjectList &def) {
  for (auto &p : def.pl) {
    auto f = tuples[p.in_table_index]->GetField(p.in_field_index);
    output->PutField(p.out_field_index, f);
  }
}

std::unique_ptr<QuerySchema> MergeSchema(std::vector<QuerySchema *> &schemas,
                                         const ProjectList &def) {
  std::unique_ptr<QuerySchema> output =
      std::make_unique<QuerySchema>(def.pl.size());
  for (auto &p : def.pl) {
    output->PutField(p.out_field_index,
                     *schemas.at(p.in_table_index)->GetField(p.in_field_index));
  }
  return output;
}

std::unique_ptr<QueryTable> Join(QueryTable *left, QueryTable *right,
                                 const JoinDef &def) {
  // auto qt =
  // std::make_unique<QueryTable>(left->GetNumTuples()*right->GetNumTuples());
  QueryTuple *pre_allocated = static_cast<QueryTuple *>(malloc(
      sizeof(QueryTuple) * left->GetNumTuples() * right->GetNumTuples()));
  ProjectList pdef;
  pdef.pl.emplace_back(0, 0, 0);
  pdef.pl.emplace_back(1, 0, 1);
  pdef.pl.emplace_back(1, 1, 2);

  int index = 0;
  for (auto &lt : *left) {
    for (auto &rt : *right) {
      expression::Expression ex(lt.GetField(def.left_index)->GetValue(),
                                rt.GetField(def.right_index)->GetValue(),
                                def.id);

      QueryTuple *t[10];
      t[0] = &lt;
      t[1] = &rt;
      auto output = ex.execute();

      pre_allocated[index].SetIsEncrypted(left->GetIsEncrypted());
      pre_allocated[index].InitDummy();
      MergeTuples(&pre_allocated[index], t, pdef);
      pre_allocated[index].SetDummyFlag(&output);
      // qt->PutTuple(std::move(tmp));
      index++;
    }
  }
  std::cout << sizeof(QueryTuple) << "," << sizeof(types::Value);
  return nullptr;
}
