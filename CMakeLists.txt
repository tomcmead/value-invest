cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME
    ValueInvest
)
set(SRC_DIR
    src
)
set(DOC_DIR
    docs
)
set(SRC
    ${SRC_DIR}/value_invest.cpp
)

################################
# Project
################################
project(${PROJECT_NAME})

add_subdirectory(${DOC_DIR})
add_executable(${PROJECT_NAME} ${SRC})