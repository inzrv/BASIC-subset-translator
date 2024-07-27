cmake_minimum_required(VERSION 3.24)
project(TeenyTiny)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/code")

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/emitter.cpp
    ${SOURCE_DIR}/parser.cpp
    ${SOURCE_DIR}/lexer.cpp
    ${SOURCE_DIR}/token.cpp
    ${SOURCE_DIR}/test.cpp
)

add_executable(TeenyTiny ${SOURCES})
target_include_directories(TeenyTiny PRIVATE ${SOURCE_DIR})
