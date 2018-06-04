cmake_minimum_required(VERSION 3.5)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compiler main.cpp lexer.h lexer.cpp parser.hpp parser.cpp symbol.h symbol.cpp tree.cpp tree.h codegen.cpp codegen.h comment.cpp comment.h optimizer.cpp optimizer.h utils.h)