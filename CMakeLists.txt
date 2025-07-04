cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME
    ValueInvest
)
set(SRC_DIR
    src
)
set(LIB_DIR
    lib
)
set(TEST_DIR
    test
)
set(DOC_DIR
    docs
)
set(SRC
    ${SRC_DIR}/value_invest.cpp
)
set(LIBS
    libcurl
    spdlog
    CurlHandler
    StockData
    JsonParser
    StockValuation
    FinancialReportTypes
)

set(TEST_NAME
    TestValueInvest
)

################################
# Project
################################
project(${PROJECT_NAME})

add_subdirectory(${DOC_DIR})
add_subdirectory(${LIB_DIR})
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/_deps/rapidjson-src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/curl_handler/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/stock_data/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/json_parser/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/stock_valuation/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/financial_report_types/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

################################
# Tests
################################
project(${TEST_NAME})

add_subdirectory(tests)
enable_testing()

add_executable(
    ${TEST_NAME}
    ${LIB_DIR}/curl_handler/${TEST_DIR}/curl_handler_test.cpp
)
target_include_directories(${TEST_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/_deps/rapidjson-src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_DIR}/curl_handler/include
)
target_link_libraries(
    ${TEST_NAME}
    PRIVATE
    ${LIBS}
    GTest::gtest_main
)