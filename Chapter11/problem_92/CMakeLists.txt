cmake_minimum_required (VERSION 3.7.0)
project(problem_92)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_definitions(-DCRYPTOPP_CXX11_LAMBDA)
include_directories(${LIBS_PATH}/cryptopp)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs/cryptopp)

if(BOOST_FILESYSTEM)
   include_directories(${BOOST_INCLUDE_DIR})
   link_directories(${BOOST_LIB_DIR})
   add_definitions(-DUSE_BOOST_FILESYSTEM)
else()
   if(MSVC)
      add_definitions(-DFILESYSTEM_EXPERIMENTAL)
   endif()
endif()


add_executable(problem_92 main.cpp)

if(BOOST_FILESYSTEM)
   if(UNIX)
      find_package(Boost COMPONENTS system filesystem REQUIRED)

      target_link_libraries(problem_92 ${Boost_FILESYSTEM_LIBRARY}
                                       ${Boost_SYSTEM_LIBRARY})
   endif()
endif()

target_link_libraries(problem_92 cryptopp)

set_target_properties (problem_92 PROPERTIES FOLDER "11.Cryptography")
