//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_QUERYFIELD_H
#define TESTING_QUERYFIELD_H

#include <vector>
#include <memory>
#include "emp-tool/emp-tool.h"
#include "QueryFieldDesc.h"


class QueryField {
private:
    bool is_encrypted;
    std::vector<std::unique_ptr<emp::Bit>> base_data;
    std::unique_ptr<emp::Integer> empInt;
    int bit_length;
    union val {
        int64_t int64Value;
        int32_t int32Value;
        double doubleValue;
        char *stringValue;
    } unencrypted_value{};
    const bool is_string;
    const FieldType type;
    const int field_num;

public:
    QueryField(QueryField &qf);
    QueryField(int64_t val, int field_num);
    QueryField(int32_t val, int field_num);
    QueryField(double val, int field_num);
    QueryField(char* val, int field_num);
    QueryField(std::string val, int field_num);
    [[nodiscard]] std::vector<bool> get_as_bits() const;

    [[nodiscard]] int64_t to(int64_t) const {
        return this->unencrypted_value.int64Value;
    }

    [[nodiscard]] int32_t to(int32_t) const {
        return this->unencrypted_value.int32Value;
    }

    [[nodiscard]] double to(double) const {
        return this->unencrypted_value.doubleValue;
    }

    emp::Bit *to(emp::Bit *) const {
        if (base_data.size() != 1) {
            throw;
        }
        return base_data[0].get();
    }

    emp::Integer *to(emp::Integer *) const {
        if (empInt == nullptr) {
            throw;
        }
        return empInt.get();
    }

    emp::Bit **to(emp::Bit **) const {
        std::vector<emp::Bit *> vec;
        for (auto &a: base_data) {
            vec.push_back(a.get());
        }
        return vec.data();
    }

    template<typename T>
    T get_as() const {
        T obj;
        return to(obj);
    }
};


#endif //TESTING_QUERYFIELD_H
