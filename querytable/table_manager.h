//
// Created by madhav on 1/14/20.
//

#ifndef TESTING_TABLE_MANAGER_H
#define TESTING_TABLE_MANAGER_H

#include "query_table.h"
#include <map>
#include <memory>

class TableManager {
private:
  std::map<std::string, std::unique_ptr<QueryTable>> table_map;

public:
  QueryTable *get_table(std::string s) const;
  void insert_table(std::string s, std::unique_ptr<QueryTable>);
};

#endif // TESTING_TABLE_MANAGER_H
