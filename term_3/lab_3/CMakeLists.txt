cmake_minimum_required(VERSION 3.20)

project(lab1 CXX)

set(CMAKE_CXX_STANDART 99)


add_executable(
  lab
  main.cpp
  matrix.hpp matrix.cpp
  file.hpp file.cpp
)
