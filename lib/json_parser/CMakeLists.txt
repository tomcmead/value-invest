cmake_minimum_required(VERSION 3.28.3)

set(LIB_NAME
    JsonParser
)

project(${LIB_NAME})

set(SRC_FILES
    src/json_parser.cpp
    src/income_statement_parser.cpp)

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/../../_deps/rapidjson-src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} PRIVATE 
    spdlog)