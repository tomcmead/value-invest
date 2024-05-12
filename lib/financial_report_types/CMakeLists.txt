cmake_minimum_required(VERSION 3.28.3)

set(LIB_NAME
    FinancialReportTypes
)

project(${LIB_NAME})

set(SRC_FILES
    src/financial_report_types.cpp)

add_library(${LIB_NAME} STATIC
    ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)