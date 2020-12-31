cmake_minimum_required (VERSION 3.7.0)
project(problem_84)

include_directories(
  ${LIBS_PATH}/PDF-Writer/LibPng
  ${LIBS_PATH}/PDF-Writer/ZLib
  ${LIBS_PATH}/PDF-Writer/FreeType/include
  ${LIBS_PATH}/PNGWriter)

add_executable(problem_84 main.cpp)

target_link_libraries(problem_84 PngWriter LibPng Zlib FreeType)

set_target_properties (problem_84 PROPERTIES FOLDER "10.ArchivesImagesDatabases")
