cmake_minimum_required(VERSION 3.22.1)

set(LIB_NAME
    StockValuation
)

project(${LIB_NAME})

set(SRC_FILES
    src/stock_valuation.cpp)

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/../../_deps/rapidjson-src/include)

target_link_libraries(${LIB_NAME} PRIVATE 
    spdlog
    libcurl
    CurlHandler
    JsonParser
    StockData
    FinancialReportTypes
    ErrorCodes)