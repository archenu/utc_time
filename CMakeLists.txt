cmake_minimum_required(VERSION 3.11)
project(time)
aux_source_directory(. DIR_SRCS)

message(STATUS "build my time..")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG  "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_executable(time ${DIR_SRCS})