cmake_minimum_required (VERSION 3.7.0)
project(problem_83)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

include_directories(
  ${LIBS_PATH}/PDF-Writer/LibPng
  ${LIBS_PATH}/PDF-Writer/ZLib
  ${LIBS_PATH}/PDF-Writer/FreeType/include
  ${LIBS_PATH}/PNGWriter)

add_executable(problem_83 main.cpp)

target_link_libraries(problem_83 PngWriter LibPng Zlib FreeType)

set_target_properties (problem_83 PROPERTIES FOLDER "10.ArchivesImagesDatabases")
