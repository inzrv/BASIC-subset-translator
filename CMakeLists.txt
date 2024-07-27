cmake_minimum_required(VERSION 3.24)
project(bst)

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

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
