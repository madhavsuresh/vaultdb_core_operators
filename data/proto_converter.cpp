//
// Created by madhav on 12/27/19.
//

#include "proto_converter.h"
#include "querytable/query_field_desc.h"
#include "querytable/query_schema.h"
#include "querytable/query_table.h"

FieldType get_field_type(dbquery::OIDType type) {
  switch (type) {
  case dbquery::BIGINT:
    return FieldType::INTEGER64;
  case dbquery::INTEGER:
    return INTEGER32;
  case dbquery::VARCHAR:
    return VARCHAR;
  case dbquery::NUMERIC:
  case dbquery::DOUBLE:
    return DOUBLE;
  case dbquery::TIMESTAMP:
    throw;
  case dbquery::TIME:
    throw;
  default:
    throw;
  }
}

std::unique_ptr<Schema> proto_to_schema(const dbquery::Schema &proto_schema) {
  auto s = std::make_unique<Schema>(proto_schema.numcolumns());
  for (int i = 0; i < proto_schema.numcolumns(); i++) {
    auto col_info = proto_schema.column().at(i);
    col_info.type();
    FieldDesc fd;
    fd.type = get_field_type((proto_schema.column().at(i).type()));
    fd.column_number = i;
    fd.name = proto_schema.column().at(i).name();
    s->put_field(i, fd);
  }
  return s;
}

std::unique_ptr<QuerySchema>
proto_to_query_schema(const dbquery::Schema &proto_schema) {
  auto s = std::make_unique<QuerySchema>(proto_schema.numcolumns());
  for (int i = 0; i < proto_schema.numcolumns(); i++) {
    auto col_info = proto_schema.column().at(i);
    col_info.type();
    QueryFieldDesc fd(i, col_info.is_private(), col_info.name(),
                      get_field_type(col_info.type()), col_info.tablename());
    s->put_field(i, fd);
  }
  return s;
}

FieldType proto_to_fieldtype(dbquery::OIDType oidtype) {
  switch (oidtype) {
  case dbquery::BIGINT:
    return FieldType::INTEGER64;
  case dbquery::INTEGER:
    return FieldType::INTEGER32;
  case dbquery::VARCHAR:
    return FieldType::VARCHAR;
  case dbquery::NUMERIC:
  case dbquery::DOUBLE:
    return FieldType::DOUBLE;
  case dbquery::TIMESTAMP:
  case dbquery::TIME:
  case dbquery::UNSUPPORTED:
  default:
    throw;
  }
}

std::unique_ptr<UnsecureTable> proto_to_unsecuretable(dbquery::Table t) {
  t.SerializePartialAsString() auto table = make_unique<UnsecureTable>();
  table->schema = proto_to_schema(t.schema());
  for (auto &r : t.row()) {
    Tuple tup;
    for (auto &c : r.column()) {
      FieldType type = proto_to_fieldtype(c.second.type());
      shared_ptr<Field> f;
      switch (type) {
      case INTEGER32:
        f = make_shared<Field>(type, c.second.int32field(), c.first);
        break;
      case INTEGER64:
        f = make_shared<Field>(type, c.second.int64field(), c.first);
        break;
      case VARCHAR:
        f = make_shared<Field>(type, c.second.strfield(), c.first);
        break;
      case DOUBLE:
        f = make_shared<Field>(type, c.second.doublefield(), c.first);
        break;
      default:
        throw;
      }
      tup.put_field(c.first, f);
    }
    table->put_tuple(tup);
  }
  return table;
}

std::unique_ptr<QueryTable> proto_to_querytable(const dbquery::Table &t) {
  auto query_table = make_unique<QueryTable>();
  query_table->set_schema(proto_to_query_schema(t.schema()));
  for (auto &r : t.row()) {
    std::unique_ptr<QueryTuple> tup = std::make_unique<QueryTuple>();
    for (auto &c : r.column()) {
      FieldType type = proto_to_fieldtype(c.second.type());
      shared_ptr<Field> f;
      unique_ptr<vaultdb::QueryField> qf;
      switch (type) {
      case INTEGER32:
        qf = std::make_unique<vaultdb::QueryField>(c.second.int32field(),
                                                   c.first);
        break;
      case INTEGER64:
        qf = std::make_unique<vaultdb::QueryField>(c.second.int64field(),
                                                   c.first);
        break;
      case VARCHAR:
        qf =
            std::make_unique<vaultdb::QueryField>(c.second.strfield(), c.first);
        break;
      case DOUBLE:
        qf = std::make_unique<vaultdb::QueryField>(c.second.doublefield(),
                                                   c.first);
        break;
      default:
        throw;
      }
      tup->put_field(c.first, *qf);
    }
    query_table->put_tuple(std::move(tup));
  }
  return query_table;
}
