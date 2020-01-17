//
// Created by madhav on 12/28/19.
//
#include "pqxx_compat.h"
#include "proto_converter.h"
#include <gtest/gtest.h>

class proto_converter_test : public ::testing::Test {
protected:
  void SetUp() override{};

  void TearDown() override{};
};

TEST_F(proto_converter_test, schema_conversion) {
  auto res = query("dbname=tpch_sf1", "SELECT * FROM customer LIMIT 10");
  auto schema = GetSchemaFromQuery(res);
  auto new_schema = ProtoToSchema(schema);
  std::cout << std::endl;
  for (int i = 0; i < new_schema->get_num_fields(); i++) {
    std::cout << i << ", " << new_schema->get_field(i)->name << std::endl;
  }
}

TEST_F(proto_converter_test, table_conversion) {
  auto table =
      GetPqTable("dbname=tpch_sf1", "SELECT l_orderkey FROM lineitem LIMIT 10");
  auto t = ProtoToUnsecuretable(table);
  for (int i = 0; i < t->num_tuples(); i++) {
    std::cout << "(";
    for (int j = 0; j < t->schema->get_num_fields(); j++) {
      std::cout << t->get_tuple(i).get_field(j)->get_string();
      std::cout << ",";
    }
    std::cout << ")" << std::endl;
  }
}

TEST_F(proto_converter_test, query_table_conversion) {
  auto table = GetPqTable(
      "dbname=tpch_sf1", "SELECT l_orderkey, l_partkey FROM lineitem LIMIT 10");
  auto t = ProtoToQuerytable(table);
  for (const auto &tup : *t) {
    std::cout << tup.get_field(0)->get_as<int64_t>() << ", "
              << tup.get_field(1)->get_as<int64_t>() << std::endl;
  }
  QueryField *qf = new QueryFieldInt32(0, 1);
  std::vector<QueryField> f;
  //qf->get_as<emp::Bit **>();
}