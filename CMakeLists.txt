cmake_minimum_required(VERSION 3.11)
project(stdx C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "-std=c23 -Wall -Werror -Wextra -Wpedantic")
set(CMAKE_C_STANDARD 23)

find_package(OpenMP)

if (OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -fopenmp")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

  add_compile_definitions(OMP_THREADS_NUM=12)
endif()

add_library(munit munit/munit.c munit/munit.h)
target_include_directories(munit PUBLIC munit/)
enable_testing()

add_subdirectory(stdx)
