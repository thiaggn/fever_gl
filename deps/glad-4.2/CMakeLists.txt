cmake_minimum_required(VERSION 3.28)
project(glad)

set(CMAKE_C_STANDARD 17)

add_library(glad "src/glad.c")
target_include_directories(glad PUBLIC "include")