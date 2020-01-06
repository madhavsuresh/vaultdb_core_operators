//
// Created by madhav on 12/26/19.
//

#include <cstring>
#include <iostream>
#include <cassert>
#include "UnsecureTable.h"

Field::Field() : is_string(false), type(FieldType::INTEGER32), field_num(0) { throw; }

void UnsecureTable::put_tuple(Tuple t) {
    tuples.push_back(t);
}

Tuple UnsecureTable::get_tuple(int index) const {
    return this->tuples[index];
}


void Tuple::put_field(int index, shared_ptr<Field> f) {
    fields.emplace(index, f);
}

shared_ptr<Field> Tuple::get_field(int index) {
    return this->fields[index];
}

UnsecureTable::UnsecureTable() {}

int UnsecureTable::num_tuples() const {
    return this->tuples.size();
}

Schema *UnsecureTable::get_schema() const {
    return schema.get();
}


Schema::Schema(int num_fields) {
    this->num_fields = num_fields;
}

void Schema::put_field(int index, FieldDesc& fd) {
    this->fields.emplace(index, make_unique<FieldDesc>(fd));
}

int Schema::get_num_fields() const {
    return num_fields;
}

FieldDesc *Schema::get_field(int i) const {
    return this->fields.at(i).get();
}

Field::Field(FieldType t, int64_t val, int fn) : is_string(false), type(t), field_num(fn) {
    value.int64Value = val;
}

Field::Field(FieldType t, double val, int fn) : is_string(false), type(t), field_num(fn) {
    value.doubleValue = val;
}

Field::Field(FieldType t, int32_t val, int fn) : is_string(false), type(t), field_num(fn) {
    value.int32Value = val;
}

Field::Field(FieldType t, const string &s, int fn) : is_string(true), type(t), field_num(fn) {
    unsigned int len = s.length() + 1;
    char *tmp = (char *) malloc(len);
    strncpy(tmp, s.c_str(), len);
    tmp[len - 1] = '\0';
    if (s.length() > 128) {
        throw;
    }
    this->value.stringValue = tmp;
    assert(strlen(this->value.stringValue) == (s.length()));
}


string Field::get_as_string() const {
    if (!is_string) throw;
    return std::string(value.stringValue);
}

int32_t Field::get_as_int32() const {
    return value.int32Value;
}

int64_t Field::get_as_int64() const {
    return value.int64Value;
}

double Field::get_as_double() const {
    return value.doubleValue;
}

Field::~Field() {
    //If deallocating string occurs here, then copy constructors will need to reallocate memory
    if (is_string) {
        free(value.stringValue);
    }
}

std::string Field::get_string() const {
    switch (type) {
        case INTEGER32:
            return std::to_string(this->value.int32Value);
        case INTEGER64:
            return std::to_string(this->value.int64Value);
        case VARCHAR:
            return std::string(this->value.stringValue);
        case DOUBLE:
            return std::to_string(this->value.doubleValue);
        default:
            throw;
    }
}


std::vector<bool> Field::get_as_bits() const {
    std::vector<bool> bits;
    switch (type) {
        case INTEGER32:
            for (unsigned int i = 0; i < sizeof(int32_t); i++) {
                bool b;
                unsigned int one = 0x1;
                b = (one << i) & (uint32_t) this->value.int32Value;
                bits.push_back(b);
            }
            break;
        case INTEGER64:
            for (unsigned int i = 0; i < sizeof(int64_t); i++) {
                bool b;
                unsigned int one = 0x1;
                b = (one << i) & (uint64_t) this->value.int64Value;
                bits.push_back(b);
            }
            break;
        default:
            throw;
    }
    return bits;
}

size_t FieldDesc::get_field_size() const {
    switch (type) {
        case INTEGER32: {
            return sizeof(uint32_t);
        }
        case INTEGER64 : {
            return sizeof(uint64_t);
        }
        case DOUBLE: {
            return sizeof(double);
        }
        default:
            throw;
    }
}

FieldDesc::FieldDesc(FieldDesc &f) {
    this->type = f.type;
    this->name = f.name;
    this->column_number = f.column_number;
    this->table_name = f.table_name;
}

FieldDesc::FieldDesc() {

}

int SecureTable::get_num_tuples() const {
    return num_tuples;
}

BaseData *SecureTable::get_base_data() {
    return base_data.get();
}

SecureTable::SecureTable() {
    base_data = make_unique<BaseData>();
}

std::vector<emp::Bit *> BaseData::get_bit_range(int start, int end) const {
    std::vector<emp::Bit *> range;
    for (int i = start; i < end; i++) {
        range.push_back(base_data[i].get());
    }
    return std::vector<emp::Bit *>();
}

void BaseData::copy_and_append(emp::Bit *to_copy) {
    this->base_data.push_back(std::make_unique<emp::Bit>(to_copy));
}
