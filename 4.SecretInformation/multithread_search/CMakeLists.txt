cmake_minimum_required(VERSION 3.14)
project(multithread_search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs -std=c++1z -pthread")

add_executable(multithread_search main.cpp KMP.cpp KMP.h file_manager.cpp file_manager.h threads_manager.cpp threads_manager.h)