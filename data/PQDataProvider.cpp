//
// Created by madhav on 12/31/19.
//

#include "PQDataProvider.h"

unique_ptr<UnsecureTable> PQDataProvider::get_table(std::string dbname,
                                                    std::string query_string) {
  auto proto_table = get_pq_table(dbname, query_string);
  auto t = proto_to_unsecuretable(proto_table);
  return t;
}
