cmake_minimum_required(VERSION 3.24)
project(TeenyTiny)

set(CMAKE_CXX_STANDARD 17)

add_executable(TeenyTiny main.cpp 
                         lexer.cpp
                         lexer.hpp
                         token.cpp
                         token.hpp
                         test.cpp
                         test.hpp)
