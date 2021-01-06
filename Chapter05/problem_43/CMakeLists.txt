cmake_minimum_required (VERSION 3.7.0)
project(problem_43)

add_definitions(-DINSTALL=${LIBS_PATH}/date)
include_directories(
    ${LIBS_PATH}/date/include/date
    ${LIBS_PATH}/date/include)

add_executable(problem_43 ${LIBS_PATH}/date/src/tz.cpp main.cpp)
target_link_libraries(problem_43 curl curlcpp)

set_target_properties (problem_43 PROPERTIES FOLDER "05.Datetime")
