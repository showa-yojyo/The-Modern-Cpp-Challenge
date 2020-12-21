cmake_minimum_required (VERSION 3.7.0)
project(problem_74)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../../include")
set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")

include_directories(${LIBS_PATH}/pugixml)

add_executable(problem_74 ${LIBS_PATH}/pugixml/pugixml.cpp main.cpp)

set_target_properties (problem_74 PROPERTIES FOLDER "09.DataSerialization")
