cmake_minimum_required(VERSION 3.10)

project(hello_opengl)
add_executable(hello_opengl WIN32 src/main.cpp)

target_sources(hello_opengl PRIVATE src/windowHandler.cpp src/gameShader.cpp src/gameProgram.cpp)

# Add GLFW to build
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw)
target_link_libraries(hello_opengl glfw)

# Add GLEW to build
add_definitions(-DGLEW_STATIC)
set(GLEW_USE_STATIC_LIBS TRUE)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew")
find_package(GLEW REQUIRED)
include_directories(hello_opengl ${GLEW_INCLUDE_DIRS})
target_link_libraries(hello_opengl ${GLEW_LIBRARIES})
target_link_libraries(hello_opengl ${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/lib/Release/x64/glew32.lib)

# Add OpenGL to build
find_package(OpenGL REQUIRED)
include_directories(hello_opengl ${OPENGL_INCLUDE_DIRS})
target_link_libraries(hello_opengl ${OPENGL_LIBRARIES})
