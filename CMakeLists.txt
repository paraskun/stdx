cmake_minimum_required(VERSION 3.11)
project(stdx C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -Wpedantic -std=c23 -fopenmp")
set(CMAKE_C_STANDARD 23)

enable_testing()

add_library(munit munit/munit.c munit/munit.h)
target_include_directories(munit PUBLIC munit/)

add_subdirectory(stdx)
