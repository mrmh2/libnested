cmake_minimum_required(VERSION 2.8.11)

project(libnested)

SET(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")

add_executable(nestest nestest.cpp models.cpp)