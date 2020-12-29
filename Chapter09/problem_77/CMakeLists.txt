cmake_minimum_required (VERSION 3.7.0)
project(problem_77)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../../include")
set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")

include_directories(
    ${LIBS_PATH}/PDF-Writer
    ${LIBS_PATH}/PDF-Writer/FreeType/include
    ${INCLUDE_PATH})

link_directories(
   ${LIBS_PATH}/ZipLib/build
   ${LIBS_PATH}/PDF-Writer/build/PDFWriter
   ${LIBS_PATH}/PDF-Writer/build/FreeType
   ${LIBS_PATH}/PDF-Writer/build/LibAesgm
   ${LIBS_PATH}/PDF-Writer/build/LibJpeg
   ${LIBS_PATH}/PDF-Writer/build/LibPng
   ${LIBS_PATH}/PDF-Writer/build/LibTiff
   ${LIBS_PATH}/PDF-Writer/build/ZLib)

if(BOOST_OPTIONAL)
   include_directories(${BOOST_INCLUDE_DIR})
   link_directories(${BOOST_LIB_DIR})
   add_definitions(-DUSE_BOOST_OPTIONAL)
endif()

add_executable(problem_77 main.cpp)

target_link_libraries(
   problem_77
   ZipLib
   PDFWriter
   FreeType
   LibAesgm
   LibJpeg
   LibPng
   LibTiff
   Zlib)

set_target_properties (problem_77 PROPERTIES FOLDER "09.DataSerialization")
