cmake_minimum_required(VERSION 3.10)

project(hello_opengl)
add_executable(hello_opengl WIN32 prjs/hello_opengl/src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)
target_link_libraries(hello_opengl glfw)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew")
find_package(GLEW REQUIRED)
include_directories(hello_opengl ${GLEW_INCLUDE_DIRS})
target_link_libraries(hello_opengl ${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(hello_opengl ${OPENGL_LIBRARIES})
