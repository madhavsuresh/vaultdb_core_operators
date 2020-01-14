//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERYTUPLE_H
#define TESTING_QUERYTUPLE_H

#include <vector>
#include <memory>
#include <map>
#include "QueryField.h"
#include "DummyFlag.h"

class QueryTuple {
private:
    int num_fields;
    //TODO(madhavsuresh): this should be const
    std::map<int, std::unique_ptr<const QueryField>> fields;
    DummyFlag flag;
public:
    QueryTuple(QueryTuple &t);

    QueryTuple();

    const QueryField *get_field(int ordinal) const;

    const QueryField *get_field(string name) const;

    void set_dummy_flag(emp::Bit &flag);

    void set_dummy_flag(bool flag);

    /* Iterator Utilities */
    typedef typename std::map<int, std::unique_ptr<const QueryField>>::iterator iterator;
    typedef typename std::map<int, std::unique_ptr<const QueryField>>::const_iterator const_iterator;

    iterator begin() { return fields.begin(); }

    const_iterator begin() const { return fields.begin(); }

    const_iterator cbegin() const { return fields.cbegin(); }

    iterator end() { return fields.end(); }

    const_iterator end() const { return fields.end(); }

    const_iterator cend() const { return fields.cend(); }
};


#endif //TESTING_QUERYTUPLE_H
