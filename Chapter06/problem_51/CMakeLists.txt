cmake_minimum_required (VERSION 3.7.0)
project(problem_51)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall -pthread")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

add_executable(problem_51 main.cpp)

set_target_properties (problem_51 PROPERTIES FOLDER "06.AlgorithmsDataStructures")
