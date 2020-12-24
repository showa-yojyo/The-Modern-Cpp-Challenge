cmake_minimum_required (VERSION 3.7.0)
project(problem_98)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

add_definitions(-DCURL_STATICLIB)

set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../../include")
set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")

include_directories(${LIBS_PATH}/curl/include)
include_directories(${LIBS_PATH}/curlcpp/include)
link_directories(${LIBS_PATH}/curlcpp/build/src)

add_executable(problem_98 main.cpp)

target_link_libraries(problem_98 curl curlcpp)

if (UNIX)
   link_directories(${CURLCPP_LIB_LOCATION})
elseif(WIN32)
   target_link_libraries(problem_98 Crypt32.lib ws2_32.lib winmm.lib wldap32.lib)
endif()

set_target_properties (problem_98 PROPERTIES FOLDER "12.NetworkingCloud")
