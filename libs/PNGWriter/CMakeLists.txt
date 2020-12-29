cmake_minimum_required (VERSION 3.7.0)
project(PngWriter)

set(LIBS_PATH "${CMAKE_SOURCE_DIR}/..")

include_directories(
    ${LIBS_PATH}/PDF-Writer/LibPng
    ${LIBS_PATH}/PDF-Writer/ZLib
    ${LIBS_PATH}/PDF-Writer/FreeType/include)

file(GLOB headers *.h)
file(GLOB sources *.cc)

add_library (PngWriter STATIC ${headers} ${sources})

target_link_libraries(
    PngWriter LibPng FreeType)

set_target_properties (PngWriter PROPERTIES FOLDER "00.Libs")
