//
// Created by madhav on 12/31/19.
//

#ifndef TESTING_PQDATAPROVIDER_H
#define TESTING_PQDATAPROVIDER_H

#include "DataProvider.h"
#include "pqxx_compat.h"
#include "proto_converter.h"

class PQDataProvider : DataProvider {

public:
    unique_ptr<UnsecureTable> get_table(std::string dbname, std::string query_string);
};


#endif //TESTING_PQDATAPROVIDER_H