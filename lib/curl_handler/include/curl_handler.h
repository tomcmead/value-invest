#pragma once

#include <curl/curl.h>
#include <string>

namespace curl_setup
{
    constexpr long kHttp_bad_request = 300;
    constexpr long kCurl_timeout_ms = 50000;
}

/// @brief cURL library API handler
/// 'Singleton' and 'Facade' design patterns
class CurlHandler
{
public:
    CurlHandler(CurlHandler const&) = delete;
    CurlHandler& operator=(CurlHandler const&) = delete;
    virtual ~CurlHandler();
    static CurlHandler* GetInstance();
    static void DeleteInstance();

    long PerformHttpGet(const std::string url, std::string& response) const;
private:
    CurlHandler();
    static size_t CurlWriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    static CurlHandler* curl_handler_instance;
    CURL* curl_handle;
};