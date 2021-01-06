cmake_minimum_required (VERSION 3.7.0)
project(problem_59)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(problem_59 main.cpp)

set_target_properties (problem_59 PROPERTIES FOLDER "06.AlgorithmsDataStructures")
