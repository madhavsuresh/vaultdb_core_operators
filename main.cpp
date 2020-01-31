//
// Created by madhav on 12/20/19.
//
#include "emp-tool/emp-tool.h"
#include "gflags/gflags.h"
#include "emp-sh2pc/emp-sh2pc.h"
#include "data/UnsecureTable.h"
#include "data/PQDataProvider.h"
#include "data/ShareData.h"
#include "operators/secure_join.h"


DEFINE_int32(party, 1, "party for EMP execution");
DEFINE_int32(port, 43439, "port for EMP execution");
DEFINE_string(hostname, "127.0.0.1", "hostname for execution");
DEFINE_bool(input, false, "input value");
DEFINE_int32(int_input, 10, "int_intput");


int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true /* remove_flags */);
    emp::NetIO *io = new emp::NetIO(FLAGS_party == emp::ALICE ? nullptr : FLAGS_hostname.c_str(), FLAGS_port);
    setup_semi_honest(io, FLAGS_party);

    PQDataProvider pq = PQDataProvider();
    auto t = pq.GetTable("dbname=tpch_sf1",
                         "SELECT l_orderkey FROM lineitem LIMIT 10");
    auto shared = ShareData(t.get(), FLAGS_party);

    JoinDef x = {.left_index = 0, .right_index=0};
    EmpJoin(shared.get(), shared.get(), x);
    //shared.reset();
}
