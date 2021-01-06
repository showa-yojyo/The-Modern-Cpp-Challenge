cmake_minimum_required (VERSION 3.7.0)
project(problem_47)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(problem_47 main.cpp)

set_target_properties (problem_47 PROPERTIES FOLDER "06.AlgorithmsDataStructures")
