cmake_minimum_required( VERSION 3.12 )
project( fenc LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra \
    -Wold-style-cast -Wuseless-cast -Wnull-dereference \
    -Werror -Wfatal-errors -pedantic -pedantic-errors"
)

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/third_party/ecfcpp )

add_library( fenc INTERFACE )
target_link_libraries( fenc INTERFACE ecfcpp m )
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

add_executable( hw03e02 ${CMAKE_CURRENT_LIST_DIR}/src/homework_03/example_02/main.cpp )
target_link_libraries( hw03e02 PRIVATE fenc )

add_executable( hw03t01 ${CMAKE_CURRENT_LIST_DIR}/src/homework_03/task_01/main.cpp )
target_link_libraries( hw03t01 PRIVATE fenc )

add_executable( hw03t03 ${CMAKE_CURRENT_LIST_DIR}/src/homework_03/task_03/main.cpp )
target_link_libraries( hw03t03 PRIVATE fenc )


add_executable( hw06f1generator ${CMAKE_CURRENT_LIST_DIR}/src/homework_06/data_generator/f1.cpp )
target_link_libraries( hw06f1generator PRIVATE fenc )

add_executable( hw06online_gradient_descent ${CMAKE_CURRENT_LIST_DIR}/src/homework_06/online_gradient_descent/main.cpp )
target_link_libraries( hw06online_gradient_descent PRIVATE fenc )

add_executable( hw06gradient_descent ${CMAKE_CURRENT_LIST_DIR}/src/homework_06/gradient_descent/main.cpp )
target_link_libraries( hw06gradient_descent PRIVATE fenc )


add_executable( hw07playground ${CMAKE_CURRENT_LIST_DIR}/src/homework_07/playground/main.cpp )
target_link_libraries( hw07playground PRIVATE fenc )
