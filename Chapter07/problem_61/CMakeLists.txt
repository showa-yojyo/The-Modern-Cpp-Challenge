cmake_minimum_required (VERSION 3.7.0)
project(problem_61)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(problem_61 main.cpp)

set_target_properties (problem_61 PROPERTIES FOLDER "07.Concurrency")
