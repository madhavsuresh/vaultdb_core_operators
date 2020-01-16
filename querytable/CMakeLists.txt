add_library(query_table
        query_field_desc.cpp
        query_schema.cpp
        query_field.cpp
        query_tuple.cpp
        query_table.cpp
        dummy_flag.cpp
        dummy_flag.h
        table_manager.cpp
        table_manager.h)
target_link_libraries(query_table types)
add_subdirectory(types)

add_executable(query_field_test query_field_test.cpp)
target_link_libraries(query_field_test query_table)
add_test(NAME query_field_test COMMAND query_field_test)
