cmake_minimum_required(VERSION 3.22.1)

set(LIB_NAME
    ErrorCodes
)

project(${LIB_NAME})

set(SRC_FILES
    src/error_codes.cpp)

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)