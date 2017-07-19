cmake_minimum_required(VERSION 3.7)
project(Linux)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h)
add_library(Linux SHARED ${SOURCE_FILES})