################################
# cURL
################################
include(FetchContent)
set(CURL_VERSION curl-8.7.1)
FetchContent_Declare(
    curl
    URL https://github.com/curl/curl/releases/download/curl-8_7_1/curl-8.7.1.tar.gz
)
set(BUILD_STATIC_LIBS ON CACHE INTERNAL "")
set(BUILD_STATIC_CURL ON CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(curl)

################################
# spdlog
################################
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(curl_handler)
add_subdirectory(stock_data)
add_subdirectory(json_parser)
add_subdirectory(stock_valuation)
add_subdirectory(financial_report_types)