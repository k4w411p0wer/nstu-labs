cmake_minimum_required(VERSION 3.0 FATAL_ERROR)


project("CourseWork" LANGUAGES CXX
                     VERSION "0.0.1"
                     DESCRIPTION "Maybe later")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

option(BUILD_TESTS "Build with unit-tests" ON)
# option(BUILD_DOCS "Build doxygen generated docs" ON)



if (BUILD_TESTS)
  enable_testing()
endif()

add_subdirectory(src)
