add_library(types
        value.cpp
        type.cpp
        arithmetic_type.cpp
        encrypted/encrypted_integer_type.cpp
        unencrypted/integer_type.cpp
        bool_result.cpp
        type_id.h
        ../expression/expression.cpp ../expression/expression.h ../expression/expression_id.h ../expression/bool_expression.cpp ../expression/bool_expression.h ../expression/arithmetic_expression.cpp ../expression/arithmetic_expression.h)
