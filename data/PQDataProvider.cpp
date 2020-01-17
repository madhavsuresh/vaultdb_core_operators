//
// Created by madhav on 12/31/19.
//

#include "PQDataProvider.h"

unique_ptr<UnsecureTable> PQDataProvider::GetTable(std::string dbname,
                                                    std::string query_string) {
  auto proto_table = GetPqTable(dbname, query_string);
  auto t = ProtoToUnsecuretable(proto_table);
  return t;
}
