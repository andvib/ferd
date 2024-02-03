add_library(ferd_lib INTERFACE)

add_subdirectory(framework)
target_link_libraries(ferd_lib INTERFACE ferd_framework)

add_subdirectory(game)
target_link_libraries(ferd_lib INTERFACE ferd_game)
