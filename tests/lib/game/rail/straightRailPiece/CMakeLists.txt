package_add_test(straight_rail_piece_test straight_rail_piece_test.cpp)

target_link_libraries(straight_rail_piece_test ferdprj)
include_directories(ferd ${PROJECT_SOURCE_DIR}/include)
include_directories(ferd ${PROJECT_SOURCE_DIR}/tests/mocks)

target_sources(straight_rail_piece_test PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/game/rail/railPiece.cpp
    ${PROJECT_SOURCE_DIR}/lib/game/rail/straightRailPiece.cpp)