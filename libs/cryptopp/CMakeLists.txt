cmake_minimum_required (VERSION 3.7.0)
project(cryptopp)

add_definitions(
    -DNDEBUG
    -DUSE_PRECOMPILED_HEADERS
    -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_library (cryptopp STATIC ${headers} ${sources})

set_target_properties (cryptopp PROPERTIES FOLDER "00.Libs")
