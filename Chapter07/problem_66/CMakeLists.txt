cmake_minimum_required (VERSION 3.7.0)
project(problem_66)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(problem_66 main.cpp)

set_target_properties (problem_66 PROPERTIES FOLDER "07.Concurrency")
