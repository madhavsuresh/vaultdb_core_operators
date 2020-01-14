//
// Created by madhav on 1/6/20.
//

#ifndef TESTING_SECUREJOIN_H
#define TESTING_SECUREJOIN_H

struct FieldMap {
    int input_field;
    int output_field;
};

enum MERGE_SIDE {LEFT, RIGHT};

struct MergeIndex {
    int in_table_index;
    int in_field_index;
    int out_field_index;
};

struct ProjectList {
    std::vector<MergeIndex> pl;
};
//Only support equi-joins for now
struct JoinDef {
    int left_index;
    int right_index;
    std::map<int,FieldMap> left_fields;
    std::map<int, FieldMap> right_fields;
};


SecureTable emp_join(SecureTable *left, SecureTable *right, const JoinDef &def);

#endif //TESTING_SECUREJOIN_H
