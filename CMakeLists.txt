cmake_minimum_required(VERSION 3.10)

# Set the C++ standard to gnu++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --static")

option(BUILD_FERD "Build the Ferd Executable" OFF)
option(BUILD_TESTS "Build the tests" OFF)

project(ferd)

add_library(ferdprj)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/spdlog/build")
find_package(spdlog REQUIRED)
target_link_libraries(ferdprj spdlog::spdlog)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/cmake")
find_package(glm REQUIRED)
target_link_libraries(ferdprj glm::glm)

include_directories(ferdprj ext)

# Add GLFW to build
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw)
target_link_libraries(ferdprj glfw)

# Add GLEW to build
add_definitions(-DGLEW_STATIC)
set(GLEW_USE_STATIC_LIBS TRUE)

# Manually specify the GLEW directories
set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/include")
set(GLEW_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/lib/Release/x64/glew32s.lib")

# Include the GLEW header directory
include_directories(${GLEW_INCLUDE_DIR})

# Add ImGui to build
file(GLOB IMGUI_SRC_FILES "ext/imgui/*.cpp")
target_sources(ferdprj PRIVATE
               ${IMGUI_SRC_FILES}
               ext/imgui/backends/imgui_impl_glfw.cpp
               ext/imgui/backends/imgui_impl_opengl3.cpp)
include_directories(ferdprj "ext/imgui")
include_directories(ferdprj "ext/imgui/backends")

# Add EIGEN to build
include_directories(ferdprj "ext/eigen/")

add_subdirectory(lib)
target_link_libraries(ferdprj ferd_lib)

if(BUILD_FERD)
    add_subdirectory(src)
endif()

if(BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# Link against the GLEW and OpenGL libraries
target_link_libraries(ferdprj ${GLEW_LIBRARY} opengl32)
