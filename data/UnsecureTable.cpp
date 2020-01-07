//
// Created by madhav on 12/26/19.
//

#include <cstring>
#include <iostream>
#include <cassert>
#include "UnsecureTable.h"
//#include "emp-tool/utils/block.h"

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

UnsecureTable::UnsecureTable() = default;

int UnsecureTable::num_tuples() const {
    return this->tuples.size();
}

Schema *UnsecureTable::get_schema() const {
    return schema.get();
}


Schema::Schema(int num_fields) {
    this->num_fields = num_fields;
    this->length_of_tuple = 0;
}

void Schema::put_field(int index, FieldDesc &fd) {
    this->fields.emplace(index, make_unique<FieldDesc>(fd));
}

int Schema::get_num_fields() const {
    return num_fields;
}

FieldDesc *Schema::get_field(int i) const {
    return this->fields.at(i).get();
}

size_t Schema::get_tuple_len() {
    if (this->length_of_tuple == 0) {
        for (int i = 0; i < this->num_fields; i++) {
            //TODO(madhavsuresh): account for dummy with plus one
            this->length_of_tuple += this->get_field(i)->get_field_size() + 1;
        }
    }
    return this->length_of_tuple;
}

size_t Schema::get_field_offset(int idx) const {
    int counter = 0;
    for (int i = 0; i < idx; i++) {
        //TODO(madhavsuresh): account for dummy with plus one
        counter += this->get_field(i)->get_field_size();
    }
    return counter;
}

Schema::Schema(Schema &s) {
    this->num_fields = s.get_num_fields();
    this->length_of_tuple = s.get_tuple_len();
    for (int i = 0; i < this->num_fields; i++) {
        this->put_field(i, *s.get_field(i));
    }
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
    this->num_tuples = 0;
}

size_t SecureTable::get_field_len(int field_idx) {
    return schema->get_field(field_idx)->get_field_size();
}

size_t SecureTable::get_tuple_len() const {
    return this->schema->get_tuple_len();
}

void SecureTable::set_dummy(int tuple_idx, emp::Bit *val) {
    // TODO(madhavsuresh): For dummy bit appended at end. I think it's more clear
    // if dummy bits are separate
    int offset = tuple_idx * (this->get_tuple_len());
    this->base_data->set_bit_at_index(offset, val);
    throw;
}

emp::Bit *SecureTable::get_bit(int tuple_idx, int field_idx, int bit_idx) {
    //base_data->get_bit_range();
}

std::vector<emp::Bit *> SecureTable::get_field_range(int tuple_idx, int field_idx) const {
    return this->base_data->get_bit_range(tuple_idx * this->get_tuple_len() + schema->get_field_offset(field_idx),
                                          tuple_idx * this->get_tuple_len()
                                          + schema->get_field(field_idx)->get_field_size());
}

SecureTable::~SecureTable() {
}

void SecureTable::set_num_tuples(int num_tuples) {
    this->num_tuples = num_tuples;
}

void SecureTable::set_schema(Schema *s) {
    this->schema = make_unique<Schema>(*s);
}

std::vector<emp::Bit *> BaseData::get_bit_range(int start, int end) const {
    std::vector<emp::Bit *> range;
    for (int i = start; i < end; i++) {
        range.push_back(base_data[i].get());
    }
    return range;
}

void BaseData::copy_and_append(emp::Bit *to_copy) {
    this->base_data.push_back(std::make_unique<emp::Bit>(to_copy->bit));
}

int BaseData::get_length() const {
    return base_data.size();
}

void BaseData::set_bit_at_index(int bit_idx, emp::Bit *b) {
    memcpy(&base_data[bit_idx].get()->bit, &b->bit, sizeof(emp::block));
}
