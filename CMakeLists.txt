cmake_minimum_required( VERSION 3.12 )
project( fenc LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_library( fenc INTERFACE )
target_include_directories( fenc INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include )

add_library( fmt INTERFACE )
target_include_directories( fmt INTERFACE ${CMAKE_CURRENT_LIST_DIR}/third_party/fmt/include )

add_executable( hw01t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_01/task_01/main.cpp )
target_link_libraries( hw01t01 PRIVATE fmt fenc )
