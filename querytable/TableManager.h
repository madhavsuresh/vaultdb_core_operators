//
// Created by madhav on 1/14/20.
//

#ifndef TESTING_TABLEMANAGER_H
#define TESTING_TABLEMANAGER_H

#include <map>
#include <memory>
#include "QueryTable.h"

class TableManager {
private:
    std::map<std::string, std::unique_ptr<QueryTable>> table_map;
public:
    QueryTable *get_table(std::string s) const;
    void insert_table(std::string s, std::unique_ptr<QueryTable>);
};


#endif //TESTING_TABLEMANAGER_H
