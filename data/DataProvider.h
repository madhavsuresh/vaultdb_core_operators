//
// Created by madhav on 12/30/19.
//

#ifndef TESTING_DATAPROVIDER_H
#define TESTING_DATAPROVIDER_H

#include "UnsecureTable.h"
#include "dbquery.pb.h"

class DataProvider {
public:
    unique_ptr<UnsecureTable> get_table(std::string dbname, std::string query_string);
};


#endif //TESTING_DATAPROVIDER_H
