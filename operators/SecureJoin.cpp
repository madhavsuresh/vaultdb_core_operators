//
// Created by madhav on 1/6/20.
//


#include "data/UnsecureTable.h"
#include "SecureJoin.h"
#include "emp-tool/emp-tool.h"


emp::Bit run_join_equality_condition(SecureField *f1, SecureField *f2, const JoinDef def) {
    if (f1->get_field_len() != f1->get_field_len()) {
        emp::Bit b(false, emp::ALICE);
        return b;
    }
    emp::Bit res(true, emp::ALICE);
    for (int offset = 0; offset < f1->get_field_len(); offset++) {
        res = res & (f1->get_bit(offset) == f2->get_bit(offset));
    }
    return res;
}

void check_equality(SecureField f1, SecureField f2) {

}

//when merging, take two tuples, project out the fields that are needed, then copy the bits into a new base table.
void merge_and_append(SecureTable *output, SecureTable *t1, SecureTable *t2, ) {
}


SecureTable emp_join(SecureTable *left, SecureTable *right, const JoinDef def) {
    def.left_index;
    def.right_index;
    //TODO(madhavsuresh): simple nested loop join
    for (int l_tup_idx = 0; l_tup_idx < left->get_num_tuples(); l_tup_idx++) {
        for (int r_tup_idx = 0; r_tup_idx < right->get_num_tuples(); r_tup_idx++) {
            auto l_tup = left->get_tuple(l_tup_idx);
            auto r_tup = right->get_tuple(r_tup_idx);
            auto join_out = run_join_equality_condition(
                    l_tup->get_field(def.left_index),
                    r_tup->get_field(def.right_index),
                    def);
        }
    }
}
