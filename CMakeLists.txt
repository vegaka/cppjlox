cmake_minimum_required(VERSION 3.13)
project(cppjlox VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppjlox)

add_subdirectory(src)