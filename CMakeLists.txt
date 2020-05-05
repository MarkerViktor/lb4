cmake_minimum_required(VERSION 3.16)
project(lb4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lb4 main.cpp Dict.h LinkedList.h String.h String.cpp)