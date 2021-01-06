cmake_minimum_required (VERSION 3.7.0)
project(problem_91)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_definitions(-DCRYPTOPP_CXX11_LAMBDA)
include_directories(${LIBS_PATH}/cryptopp)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs/cryptopp)

add_executable(problem_91 main.cpp)

target_link_libraries(problem_91 cryptopp)

set_target_properties (problem_91 PROPERTIES FOLDER "11.Cryptography")
