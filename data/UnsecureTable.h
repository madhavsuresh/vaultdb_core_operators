//
// Created by madhav on 12/26/19.
//

#ifndef TESTING_UNSECURETABLE_H
#define TESTING_UNSECURETABLE_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <variant>
#include "emp-tool/emp-tool.h"


using namespace std;

enum FieldType {
    UNSUPPORTED,
    INTEGER32,
    INTEGER64,
    VARCHAR,
    DOUBLE,
    NUMERIC,
    TIMESTAMP,
    TIME,
    BIGINT
};

struct FieldDesc {
    FieldDesc();

    int column_number;
    string name;
    FieldType type;
    // origin table name
    string table_name;

    FieldDesc(FieldDesc &f);

    [[nodiscard]] size_t get_field_size() const;
};


struct Field {
private:
    union val {
        int64_t int64Value;
        int32_t int32Value;
        double doubleValue;
        char *stringValue;
    } value{};
    const bool is_string;
    const FieldType type;
    const int field_num;

public:
    Field();

    Field(FieldType type, int64_t val, int field_num);

    Field(FieldType type, int32_t val, int field_num);

    Field(FieldType type, double val, int field_num);

    Field(FieldType type, const std::string &s, int field_num);


    ~Field();

    //Field(const Field &f);

    [[nodiscard]] std::string get_as_string() const;

    [[nodiscard]] int64_t get_as_int64() const;

    [[nodiscard]] int32_t get_as_int32() const;

    [[nodiscard]] double get_as_double() const;

    [[nodiscard]] std::vector<bool> get_as_bits() const;

    std::string get_string() const;
};


struct Schema {
private:
    std::map<int, std::unique_ptr<FieldDesc>> fields;
    int num_fields;
    size_t length_of_tuple;
public:
    [[nodiscard]] int get_num_fields() const;

    std::map<std::string, int> nameToIndex;

    void put_field(int, FieldDesc &fd);

    size_t get_tuple_len();

    size_t get_field_offset(int field_num) const;

    explicit Schema(int num_fields);

    Schema(Schema &s);

    [[nodiscard]] FieldDesc *get_field(int i) const;
};

struct Tuple {
private:
    std::map<int, shared_ptr<Field>> fields;
public:
    bool is_dummy;

    void put_field(int index, shared_ptr<Field> f);

    shared_ptr<Field> get_field(int index);

    Field get_field(string name);

    void set_dummy();
};


struct UnsecureTable {

    std::vector<Tuple> tuples;
    //TODO(madhavsuresh): figure out pointers for this.
    unique_ptr<Schema> schema2;
    std::unique_ptr<Schema> schema;

    UnsecureTable();

    Tuple get_tuple(int index) const;

    void put_tuple(Tuple t);

    int num_tuples() const;

    //TODO(madhavsuresh): not sure how memory allocation
    // works in c++. Need to pass a copy, or a reference
    // to the schema
    Schema *get_schema() const;
};

struct BaseData {
private:
    std::vector<std::unique_ptr<emp::Bit>> base_data;
public:
    //[start, end)
    [[nodiscard]] std::vector<emp::Bit *> get_bit_range(int start, int end) const;

    void copy_and_append(std::vector<emp::Bit *> to_copy);

    int get_length() const;

    void set_bit_at_index(int bit_idx, emp::Bit *b);

    void copy_and_append(emp::Bit *to_copy);
};

struct SecureField {
private:
    FieldType type;
    BaseData *base_data;
    int field_len;
    //[start, end)
    int start_base_idx;
    int end_base_idx;
    int start_tuple_idx;
    int end_tuple_idx;
public:
    emp::Integer get_as_Integer64();

    emp::Integer get_as_Integer32();

    emp::Bit get_bit(int index);

    std::vector<std::shared_ptr<emp::Bit>> get_as_BitVector();

    std::shared_ptr<emp::Bit> is_equal(SecureField &f);

    const int get_field_len() const;
};

struct SecureTuple {
    int num_fields;
    int tuple_len;
    int tuple_no;
    int start_base_idx;
    int end_base_idx;

    BaseData *base_data;
    std::vector<std::unique_ptr<SecureField>> fields;

    SecureField *get_field(int field_idx);

    emp::Bit *is_dummy();
};

//copy on write, always copy semantics
struct SecureTable {
private:
    int num_tuples;
    int tuple_len;
    //TODO(madhavsuresh): come up with better name
    std::unique_ptr<BaseData> base_data;
    std::unique_ptr<Schema> schema;
    // enforce only one scope owning a tuple at a time.
    // there is probably a better way to do this.
public:
    SecureTable();

    ~SecureTable();

    void set_schema(Schema *s);

    [[nodiscard]] int get_num_tuples() const;

    void set_num_tuples(int num_tuples);

    unique_ptr<SecureTuple> get_tuple(int idx);

    emp::Bit *get_bit(int tuple_idx, int field_idx, int bit_idx);

    std::vector<emp::Bit *> get_field_range(int tuple_idx, int field_idx) const;

    size_t get_field_len(int field_idx);

    size_t get_tuple_len() const;

    void set_dummy(int tuple_idx, emp::Bit *val);

    BaseData *get_base_data();
};

#endif //TESTING_UNSECURETABLE_H
