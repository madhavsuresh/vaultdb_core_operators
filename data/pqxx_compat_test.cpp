//
// Created by madhav on 12/27/19.
//
#include <gtest/gtest.h>
#include "pqxx_compat.h"

class pqxx_compat_test : public ::testing::Test {
protected:

    void SetUp() override {}

    void TearDown() override {};
};

//TODO(madhavsuresh): build out these tests
TEST_F(pqxx_compat_test, get_schema) {
    auto res = query("dbname=tpch_sf1", "SELECT * FROM customer LIMIT 10");
    auto schema = get_schema_from_query(res);
    std::cout << schema.DebugString();
}

TEST_F(pqxx_compat_test, get_pq_table) {
    dbquery::Table t = get_pq_table("dbname=tpch_sf1", "SELECT * FROM customer LIMIT 10");
    std::cout << t.DebugString();
}
