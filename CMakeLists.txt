cmake_minimum_required(VERSION 3.17)
project(dining_philosophers)

find_package(Threads)

set(CMAKE_CXX_STANDARD 20)

add_executable(dining_philosophers main.cpp inc/Philosopher.h)
target_link_libraries(dining_philosophers ${CMAKE_THREAD_LIBS_INIT})