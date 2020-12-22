cmake_minimum_required (VERSION 3.7.0)
project(problem_84)

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
link_directories(
  ${LIBS_PATH}/PDF-Writer/build/LibPng
  ${LIBS_PATH}/PDF-Writer/build/ZLib
  ${LIBS_PATH}/PDF-Writer/build/FreeType
  ${LIBS_PATH}/PNGWriter/build)
include_directories(${LIBS_PATH}/PDF-Writer/LibPng)
include_directories(${LIBS_PATH}/PDF-Writer/ZLib)
include_directories(${LIBS_PATH}/PDF-Writer/FreeType/include)
include_directories(${LIBS_PATH}/PNGWriter)

add_executable(problem_84 main.cpp)

target_link_libraries(problem_84 PngWriter LibPng Zlib FreeType)

set_target_properties (problem_84 PROPERTIES FOLDER "10.ArchivesImagesDatabases")
