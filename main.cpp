//
// Created by madhav on 12/20/19.
//
#include "emp-tool/emp-tool.h"
#include "gflags/gflags.h"
#include "emp-sh2pc/emp-sh2pc.h"
#include "data/UnsecureTable.h"
#include "data/PQDataProvider.h"
#include "data/ShareData.h"


using namespace emp;
DEFINE_int32(party, 1, "party for EMP execution");
DEFINE_int32(port, 43439, "port for EMP execution");
DEFINE_string(hostname, "127.0.0.1", "hostname for execution");
DEFINE_bool(input, false, "input value");
DEFINE_int32(int_input, 10, "int_intput");


int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true /* remove_flags */);
    NetIO *io = new NetIO(FLAGS_party == ALICE ? nullptr : FLAGS_hostname.c_str(), FLAGS_port);
    setup_semi_honest(io, FLAGS_party);

    PQDataProvider pq = PQDataProvider();
    auto t = pq.get_table("dbname=tpch_sf1", "SELECT l_orderkey FROM lineitem LIMIT 10");
    share_data(t.get(), FLAGS_party);

    /*
    int len = t->num_tuples();

    vector<shared_ptr<Integer>> secrets;
    vector<unique_ptr<Bit>> bit_array;
    unique_ptr<Batcher> b = make_unique<Batcher>();
//    Integer bz(64, bit_array.);

    for (int i = 0; i < len; i++) {
        if (FLAGS_party == ALICE) {
            secrets.push_back(make_shared<Integer>(64, t->get_tuple(i).get_field(0)->get_as_int64(), ALICE));
        } else {
            secrets.push_back(make_shared<Integer>(64, 0, ALICE));
        }
    }
    auto t2 = pq.get_table("dbname=tpch_sf1", "SELECT l_orderkey FROM lineitem LIMIT 20");
    for (int i = 10; i < 10 + len; i++) {
        if (FLAGS_party == BOB) {
            secrets.push_back(make_shared<Integer>(64, t2->get_tuple(i).get_field(0)->get_as_int64(), BOB));
        } else {
            secrets.push_back(make_shared<Integer>(64, 0, BOB));
        }
    }
    int counter = 0;
    printf("WOW");
    for (auto i : secrets) {
        if (counter < 10) {
            if (FLAGS_party == BOB) {
                printf("RES: %d, %d, %d", counter, t->get_tuple(counter).get_field(0)->get_as_int64(),
                       i->reveal<int64_t>(PUBLIC));
            } else {
                i->reveal<int64_t>(PUBLIC);
            }
        } else {
            if (FLAGS_party == ALICE) {
                printf("RES: %d, %d", t2->get_tuple(counter).get_field(0)->get_as_int64(), i->reveal<int64_t>(PUBLIC));
            } else {
                i->reveal<int64_t>(PUBLIC);
            }
        }
        counter++;
    }
    /*
    for (int i = 0; i < secrets.size(); i++) {
        if (FLAGS_party == ALICE) {
            secrets[i]->reveal<int64_t>(PUBLIC);
        }
    }
     */
}






/*
Integer z;
Integer x(64, FLAGS_int_input, ALICE);
Integer y(64, FLAGS_int_input, BOB);
Batcher b;
//    if (FLAGS_party == ALICE) {
//        x = new Bit(true, FLAGS_party);
//  }
z = x + y;
if (FLAGS_party == ALICE) {
    y.reveal<int64_t>(ALICE);
}

printf("RES: %d, %d", FLAGS_int_input, y.reveal<int64_t>(PUBLIC));
printf("RES: %d, %d", FLAGS_int_input, x.reveal<int64_t>(PUBLIC));
printf("RES: %d", z.reveal<int64_t>(PUBLIC));

auto start = std::chrono::system_clock::now();
change_base("100", 10, 2);
auto end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end - start;
std::time_t end_time = std::chrono::system_clock::to_time_t(end);

std::cout << "finished computation at " << std::ctime(&end_time)
          << "elapsed time: " << elapsed_seconds.count() << "s\n";
std::cout << std::endl;
start = std::chrono::system_clock::now();
/*
int x = 100;
int tmp = x;
int result = 0;
while (x >>= 1) result++;
printf("%d\n", result);
bool data[10];
int counter = 0;
while (tmp) {
    if (tmp & 1) {
        data[counter] = 1;
    } else {
        data[counter] = 0;
    }
    tmp >>= 1;
    counter++;
}
end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds2 = end - start;
std::time_t end_time2 = std::chrono::system_clock::to_time_t(end);

std::cout << "finished computation at " << std::ctime(&end_time2)
          << "elapsed time: " << elapsed_seconds2.count() << "s\n";

//    Bit resp = ((y)&(x));
//   printf("RES: %d", resp.reveal(PUBLIC));
}
 */
