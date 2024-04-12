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