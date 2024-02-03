add_library(ferd_framework)

target_link_libraries(ferd_framework ferdprj)

target_sources(ferd_framework PRIVATE
    gameShader.cpp
    graphicsFramework.cpp
    graphicsProgram.cpp
    windowHandler.cpp
    geometry/circleObject.cpp
    geometry/lineObject.cpp
    geometry/rectangleObject.cpp)

include_directories(ferd_framework ../../include)
