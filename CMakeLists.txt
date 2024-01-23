cmake_minimum_required(VERSION 3.10)

project(max5494_max5499)
set(CMAKE_C_STANDARD 99)

include_directories(include)
add_library(max5494_max5499 STATIC
            src/max5494_max5499.c)

add_executable(test test/test.c)
target_link_libraries(test max5494_max5499)
