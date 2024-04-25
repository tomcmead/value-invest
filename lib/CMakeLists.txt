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
# RapidJSON
################################
include(FetchContent)
FetchContent_Declare(
    rapidjson
    URL https://github.com/Tencent/rapidjson/archive/refs/tags/v1.1.0.tar.gz
    FIND_PACKAGE_ARGS 1.1.0
)
set(RAPIDJSON_BUILD_DOC OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(rapidjson)

################################
# spdlog
################################
include(FetchContent)
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.tar.gz
    FIND_PACKAGE_ARGS 1.13.0
)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(curl_handler)
add_subdirectory(stock_data)
add_subdirectory(json_parser)