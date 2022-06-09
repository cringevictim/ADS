cmake_minimum_required(VERSION 3.22)
project(ADS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(WIN32)
    message(FATAL_ERROR "This is not meant for WINDOWS users((")
endif(WIN32)

message(STATUS "Adding subdirectories")
add_subdirectory("Lab1")
add_subdirectory("Lab2")
add_subdirectory("Lab3")
add_subdirectory("Lab4")
message(STATUS "Adding subdirectories - done")
