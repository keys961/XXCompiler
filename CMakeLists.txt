cmake_minimum_required(VERSION 3.5)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compiler main.cpp symbol.h symbol.cpp tree.cpp tree.h codegen.cpp codegen.h)