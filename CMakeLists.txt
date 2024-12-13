cmake_minimum_required(VERSION 3.11)
project(stdx C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "-std=c23 -Wall -Werror -Wextra -Wpedantic")
set(CMAKE_C_STANDARD 23)

add_library(munit munit/munit.c munit/munit.h)
target_include_directories(munit PUBLIC munit/)
enable_testing()

add_subdirectory(stdx)
