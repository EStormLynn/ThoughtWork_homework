cmake_minimum_required(VERSION 3.6)
project(ThoughtWork_homework)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TWType.h TWOrderManager.cpp TWOrderManager.h TWIO.cpp TWIO.h)
add_executable(ThoughtWork_homework ${SOURCE_FILES})