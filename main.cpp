//
// Created by madhav on 12/20/19.
//
#include "data/PQDataProvider.h"
#include "emp-sh2pc/emp-sh2pc.h"
#include "emp-tool/emp-tool.h"
#include "gflags/gflags.h"
#include "operators/secure_join.h"
#include "querytable/private_share_utility.h"

DEFINE_int32(party, 1, "party for EMP execution");
DEFINE_int32(port, 43439, "port for EMP execution");
DEFINE_string(hostname, "127.0.0.1", "hostname for execution");
DEFINE_bool(input, false, "input value");
DEFINE_int32(int_input, 10, "int_intput");

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true /* remove_flags */);
  emp::NetIO *io = new emp::NetIO(
      FLAGS_party == emp::ALICE ? nullptr : FLAGS_hostname.c_str(), FLAGS_port);
  setup_semi_honest(io, FLAGS_party);

  PQDataProvider pq = PQDataProvider();
  auto t = pq.GetQueryTable("dbname=tpch_sf1",
                            "SELECT l_orderkey FROM lineitem LIMIT 10");

  EmpParty my_party =
      FLAGS_party == emp::ALICE ? EmpParty::ALICE : EmpParty::BOB;
  ShareDef def;
  ShareCount ca = {.party = EmpParty::ALICE, .num_tuples = 10};
  ShareCount cb = {.party = EmpParty::BOB, .num_tuples = 10};

  def.share_map[EmpParty::ALICE] = ca;
  def.share_map[EmpParty::BOB] = cb;
  auto pt = share_data(t->GetSchema(), my_party, t.get(), def);
  std::cout << "Num tuples: " << pt->GetNumTuples();
  JoinDef x = {.left_index = 0, .right_index = 0};
  x.id = vaultdb::expression::ExpressionId::EQUAL;
  Join(pt.get(), pt.get(), x);
  pt->GetTuple(1);
}
