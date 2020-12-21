cmake_minimum_required (VERSION 3.7.0)
project(problem_78)

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

include_directories(${LIBS_PATH}/PDF-Writer)
include_directories(${LIBS_PATH}/PDF-Writer/FreeType/include)

link_directories(
   ${LIBS_PATH}/ZipLib/build
   ${LIBS_PATH}/PDF-Writer/build/PDFWriter
   ${LIBS_PATH}/PDF-Writer/build/FreeType
   ${LIBS_PATH}/PDF-Writer/build/LibAesgm
   ${LIBS_PATH}/PDF-Writer/build/LibJpeg
   ${LIBS_PATH}/PDF-Writer/build/LibPng
   ${LIBS_PATH}/PDF-Writer/build/LibTiff
   ${LIBS_PATH}/PDF-Writer/build/ZLib)

if(BOOST_FILESYSTEM)
   include_directories(${BOOST_INCLUDE_DIR})
   link_directories(${BOOST_LIB_DIR})
   add_definitions(-DUSE_BOOST_FILESYSTEM)
else()
   if(MSVC)
      add_definitions(-DFILESYSTEM_EXPERIMENTAL)
   endif()
endif()

add_executable(problem_78 main.cpp)

if(BOOST_FILESYSTEM)
   if(UNIX)
      find_package(Boost COMPONENTS system filesystem REQUIRED)

      target_link_libraries(problem_78 ${Boost_FILESYSTEM_LIBRARY}
                                       ${Boost_SYSTEM_LIBRARY})
   endif()
endif()

target_link_libraries(problem_78 ZipLib)
target_link_libraries(problem_78 PDFWriter)
target_link_libraries(problem_78 FreeType)
target_link_libraries(problem_78 LibAesgm)
target_link_libraries(problem_78 LibJpeg)
target_link_libraries(problem_78 LibPng)
target_link_libraries(problem_78 LibTiff)
target_link_libraries(problem_78 Zlib)

add_custom_command(TARGET problem_78 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_SOURCE_DIR}/res $<TARGET_FILE_DIR:problem_78>/res)

add_custom_command(TARGET problem_78 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)

set_target_properties (problem_78 PROPERTIES FOLDER "09.DataSerialization")
