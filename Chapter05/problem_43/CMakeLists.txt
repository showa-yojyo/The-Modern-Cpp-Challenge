cmake_minimum_required (VERSION 3.7.0)
project(problem_43)

set(LIBS_PATH "${CMAKE_SOURCE_DIR}/../../libs")
add_definitions(-DINSTALL=${LIBS_PATH}/date)
include_directories(${LIBS_PATH}/date/include/date)
include_directories(${LIBS_PATH}/date/include)

add_executable(problem_43 ${LIBS_PATH}/date/src/tz.cpp main.cpp)

set_target_properties (problem_43 PROPERTIES FOLDER "05.Datetime")
