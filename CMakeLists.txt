cmake_minimum_required(VERSION 3.10)

project(ferd)
add_executable(ferd WIN32 src/main.cpp)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/spdlog/build")
find_package(spdlog REQUIRED)
target_link_libraries(ferd spdlog::spdlog)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/glm/cmake")
find_package(glm REQUIRED)
target_link_libraries(ferd glm::glm)

target_sources(ferd PRIVATE
               lib/framework/windowHandler.cpp
               lib/framework/gameShader.cpp
               lib/framework/graphicsProgram.cpp
               lib/framework/graphicsFramework.cpp
               lib/framework/graphicsScreen.cpp
               lib/game/rectangleObject.cpp
               lib/game/camera.cpp
               lib/game/train.cpp
               lib/game/trainNavigator.cpp
               lib/game/trainPhysics.cpp
               lib/game/line.cpp)
include_directories(ferd include ext)

# Add GLFW to build
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw)
target_link_libraries(ferd glfw)

# Add GLEW to build
add_definitions(-DGLEW_STATIC)
set(GLEW_USE_STATIC_LIBS TRUE)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew")
find_package(GLEW REQUIRED)
include_directories(ferd ${GLEW_INCLUDE_DIRS})
target_link_libraries(ferd ${GLEW_LIBRARIES})
target_link_libraries(ferd ${CMAKE_CURRENT_SOURCE_DIR}/ext/glew/lib/Release/x64/glew32.lib)

# Add OpenGL to build
find_package(OpenGL REQUIRED)
include_directories(ferd ${OPENGL_INCLUDE_DIRS})
target_link_libraries(ferd ${OPENGL_LIBRARIES})

# Add ImGui to build
file(GLOB IMGUI_SRC_FILES "ext/imgui/*.cpp")
target_sources(ferd PRIVATE
               ${IMGUI_SRC_FILES}
               ext/imgui/backends/imgui_impl_glfw.cpp
               ext/imgui/backends/imgui_impl_opengl3.cpp)
include_directories(ferd "ext/imgui")
include_directories(ferd "ext/imgui/backends")
