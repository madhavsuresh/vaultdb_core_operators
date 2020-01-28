//
// Created by madhav on 1/15/20.
//

#include "type.h"
#include <querytable/types/unencrypted/integer_type.h>

vaultdb::types::Type *vaultdb::types::Type::GetInstance(TypeId type_id) {
  switch (type_id) {

  case TypeId::INVALID:
    break;
  case TypeId::BOOLEAN:
    break;
  case TypeId::INTEGER32:
    return new IntegerType();
  case TypeId::INTEGER64:
    return new IntegerType();
  case TypeId::FLOAT32:
    break;
  case TypeId::FLOAT64:
    break;
  case TypeId::DOUBLE:
    break;
  case TypeId::NUMERIC:
    break;
  case TypeId::TIMESTAMP:
    break;
  case TypeId::TIME:
    break;
  case TypeId::DATE:
    break;
  case TypeId::VARCHAR:
    break;
  case TypeId::ENCRYPTED_INTEGER32:
    break;
  case TypeId::ENCRYPTED_INTEGER64:
    break;
  case TypeId::ENCRYPTED_BOOLEAN:
    break;
  }
}
