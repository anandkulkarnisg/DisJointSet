cmake_minimum_required(VERSION 2.8.4)
project(DisJointSet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")

# Generate shared library libDisJointSet.so file.
ADD_LIBRARY(DisJointSet SHARED DisJointSet.cpp)

# Add test Examples below.
add_executable(Example1.out Example1.cpp)
add_executable(Example2.out Example2.cpp)

target_link_libraries(Example1.out DisJointSet)
target_link_libraries(Example2.out DisJointSet)
