package_add_test(line_test line_test.cpp)

target_link_libraries(line_test ferdprj)
include_directories(ferd ${PROJECT_SOURCE_DIR}/include)
include_directories(ferd ${PROJECT_SOURCE_DIR}/tests/mocks)
