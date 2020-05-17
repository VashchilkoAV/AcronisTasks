cmake_minimum_required(VERSION 3.16)
project(Png C)

set(CMAKE_C_STANDARD 11)

add_executable(Png main.c)

target_link_libraries(Png png z)