add_executable(ferd main.cpp)

target_link_libraries(ferd PRIVATE ferdprj)
include_directories(ferd ../include)
