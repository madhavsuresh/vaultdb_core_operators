//
// Created by madhav on 1/7/20.
//

#ifndef TESTING_QUERYTABLE_H
#define TESTING_QUERYTABLE_H

#include "emp-tool/emp-tool.h"
#include <memory>
#include "QueryTuple.h"
#include "QuerySchema.h"

class QueryTable {
private:
    std::vector<std::unique_ptr<QueryTuple>> tuples;
    std::unique_ptr<QuerySchema> schema;
public:
    typedef typename std::vector<std::unique_ptr<QueryTuple>>::iterator iterator;
    typedef typename std::vector<std::unique_ptr<QueryTuple>>::const_iterator const_iterator;
    void set_schema(std::unique_ptr<QuerySchema> s);

    iterator begin() {return tuples.begin();}
    const_iterator begin() const {return tuples.begin();}
    const_iterator cbegin() const {return tuples.cbegin();}
    iterator end() {return tuples.end();}
    const_iterator end() const {return tuples.end();}
    const_iterator cend() const {return tuples.cend();}
};

#endif //TESTING_QUERYTABLE_H
