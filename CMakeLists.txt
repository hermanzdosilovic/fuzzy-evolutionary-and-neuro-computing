cmake_minimum_required( VERSION 3.12 )
project( fenc LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -pedantic-errors" )

add_library( fenc INTERFACE )
target_include_directories( fenc INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include )

# add_library( fmt INTERFACE )
# target_include_directories( fmt INTERFACE ${CMAKE_CURRENT_LIST_DIR}/third_party/fmt/include )

add_executable( hw01t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_01/main.cpp )
target_link_libraries( hw01t01 PRIVATE fenc )

add_executable( hw01t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_02/main.cpp )
target_link_libraries( hw01t02 PRIVATE fenc )

add_executable( hw01t03 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_03/main.cpp )
target_link_libraries( hw01t03 PRIVATE fenc )

add_executable( hw02t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_01/main.cpp )
target_link_libraries( hw02t01 PRIVATE fenc )

add_executable( hw02t02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_02/main.cpp )
target_link_libraries( hw02t02 PRIVATE fenc )

add_executable( hw02t03 ${CMAKE_CURRENT_LIST_DIR}/src/homework_02/task_03/main.cpp )
target_link_libraries( hw02t03 PRIVATE fenc )

add_executable( hw03e01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_03/example_01/main.cpp )
target_link_libraries( hw03e01 PRIVATE fenc )

add_executable( hw03ship_controller ${CMAKE_CURRENT_LIST_DIR}/src/homework_03/ship_controller/main.cpp )
target_link_libraries( hw03ship_controller PRIVATE fenc )
