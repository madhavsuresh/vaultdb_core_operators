//
// Created by madhav on 1/6/20.
//


#include "data/UnsecureTable.h"
#include "SecureJoin.h"
#include "emp-tool/emp-tool.h"

std::unique_ptr<emp::Bit> equality(std::vector<emp::Bit *> r1, std::vector<emp::Bit *> r2) {
    if (r1.size() != r2.size()) {
        auto b = std::make_unique<emp::Bit>(false, emp::ALICE);
        return b;
    }
    emp::Bit b(true);
    for (int offset = 0; offset < r1.size(); offset++) {
        b = b & (*r1[offset] == *r2[offset]);
    }
    std::cout << std::endl;
    return make_unique<emp::Bit>(b.bit);
}

std::unique_ptr<emp::Bit>
run_join_equality_condition(SecureTable *left, SecureTable *right, int left_idx, int right_idx, const JoinDef &def) {
    auto left_bits = left->get_field_range(left_idx, def.left_index);
    auto right_bits = right->get_field_range(right_idx, def.right_index);
    auto eq = equality(left_bits, right_bits);
    std::cout << "Left: " << left_idx << "; Right:" << right_idx << "|" << eq->reveal<bool>(emp::PUBLIC) << std::endl;
    return eq;
}

SecureTable emp_join(SecureTable *left, SecureTable *right, const JoinDef &def) {
    //TODO(madhavsuresh): simple nested loop join
    for (int l_tup_idx = 0; l_tup_idx < left->get_num_tuples(); l_tup_idx++) {
        for (int r_tup_idx = 0; r_tup_idx < right->get_num_tuples(); r_tup_idx++) {
            auto eq = run_join_equality_condition(left, right, l_tup_idx, r_tup_idx, def);
        }
    }
}
