cmake_minimum_required(VERSION 3.10)
project(LinkedList)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE include)

add_executable(tests tests/test_list.cpp)
target_include_directories(tests PRIVATE include)
