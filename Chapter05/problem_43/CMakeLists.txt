cmake_minimum_required (VERSION 3.7.0)
project(problem_43)

if (UNIX)
  message(status "** Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fexceptions -g -Wall")
elseif(WIN32)
  message(status "** Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /std:c++latest")

  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_definitions(-DCURL_STATICLIB)

set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")
set(CURLCPP_LIB_LOCATION "${LIB_PATH}/curlcpp/build/src")
add_definitions(-DINSTALL=${LIBS_PATH}/date)
include_directories(${LIBS_PATH}/date/include/date)
include_directories(${LIBS_PATH}/date/include)
link_directories(${LIBS_PATH}/curlcpp/build/src)

add_executable(problem_43 ${LIBS_PATH}/date/src/tz.cpp main.cpp)
target_link_libraries(problem_43 curl curlcpp)

if (UNIX)
   link_directories(${CURLCPP_LIB_LOCATION})
elseif(WIN32)
   target_link_libraries(problem_97 Crypt32.lib ws2_32.lib winmm.lib wldap32.lib)
endif()

set_target_properties (problem_43 PROPERTIES FOLDER "05.Datetime")
