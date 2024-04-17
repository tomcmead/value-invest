cmake_minimum_required(VERSION 3.28.3)

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
set(DOC_DIR
    docs
)
set(SRC
    ${SRC_DIR}/value_invest.cpp
)
set(LIBS
    libcurl
    spdlog
    SQLite::SQLite3
    CurlHandler
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

find_package(SQLite3 REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/_deps/rapidjson-src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/curl_handler/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

################################
# Tests
################################
project(${TEST_NAME})

add_subdirectory(tests)
enable_testing()
add_test(${TEST_NAME} ${TEST_NAME})