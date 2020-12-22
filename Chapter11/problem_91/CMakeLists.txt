cmake_minimum_required (VERSION 3.7.0)
project(problem_91)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall -pthread")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../../include")
set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")

include_directories(${LIBS_PATH}/cryptopp)
link_directories(${LIBS_PATH}/cryptopp)

add_definitions(-DCRYPTOPP_CXX11_LAMBDA)

add_executable(problem_91 main.cpp)

target_link_libraries(problem_91 cryptopp)

set_target_properties (problem_91 PROPERTIES FOLDER "11.Cryptography")
