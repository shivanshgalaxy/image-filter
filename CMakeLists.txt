cmake_minimum_required(VERSION 3.25)
project(filter2 C)

set(CMAKE_C_STANDARD 11)

add_executable(filter2 main.c bmp.h helpers.c helpers.h)

target_link_libraries(filter2 m)
