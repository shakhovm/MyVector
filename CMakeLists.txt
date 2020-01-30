cmake_minimum_required(VERSION 3.14)
project(my_vector CXX)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(googletest-master/googletest)

add_executable(my_vector main.cpp MyVector.h)


target_link_libraries(my_vector gtest gtest_main)