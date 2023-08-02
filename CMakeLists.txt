cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage"  CACHE STRING INTERNAL FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")

project(DEMO_TDD_CXX VERSION 0.1.0)

# set(BUILD_GMOCK ON)

enable_testing()

add_subdirectory(src)

# 用于单元测试
add_subdirectory(tests)