cmake_minimum_required(VERSION 2.8.11)

project(libnested)

if(APPLE)
    SET(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
else(APPLE)
    SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_executable(nestest nestest.cpp models.cpp dataset.cpp)
add_executable(devnest devnest.cpp models.cpp dataset.cpp)
