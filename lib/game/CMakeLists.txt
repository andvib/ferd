add_library(ferd_game)

target_link_libraries(ferd_game ferdprj ferd_framework)

target_sources(ferd_game PRIVATE
    camera.cpp
    line.cpp
    train.cpp
    trainNavigator.cpp
    trainPhysics.cpp
    world.cpp)

target_sources(ferd_game PRIVATE
    rail/railConnection.cpp
    rail/railPiece.cpp
    rail/straightRailPiece.cpp
    rail/railWalker.cpp)

include_directories(ferd_framework ../../include)
