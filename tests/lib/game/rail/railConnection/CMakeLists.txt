package_add_test(rail_connection_test rail_connection_test.cpp)

target_link_libraries(rail_connection_test ferdprj)
include_directories(ferd ${PROJECT_SOURCE_DIR}/include)
include_directories(ferd ${PROJECT_SOURCE_DIR}/tests/mocks)

target_sources(rail_connection_test PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/game/rail/railConnection.cpp
    ${PROJECT_SOURCE_DIR}/lib/game/rail/straightRailPiece.cpp)