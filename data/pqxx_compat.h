//
// Created by madhav on 12/27/19.
//

#ifndef TESTING_PQXX_COMPAT_H
#define TESTING_PQXX_COMPAT_H

#include "dbquery.pb.h"
#include "dbquery.grpc.pb.h"
#include <string>
#include <pqxx/pqxx>

const dbquery::Schema get_schema_from_query(pqxx::result res);
pqxx::result query(std::string dbname, std::string query_string);
dbquery::Table get_pq_table(std::string dbname, std::string query_string);
#endif //TESTING_PQXX_COMPAT_H
