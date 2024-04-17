#pragma once

#include <curl/curl.h>
#include <string>

/// @brief cURL library API handler.
/// 'Singleton' and 'Facade' design patterns
class CurlHandler
{
public:
    CurlHandler(CurlHandler const&) = delete;
    CurlHandler& operator=(CurlHandler const&) = delete;
    virtual ~CurlHandler();
    static CurlHandler* GetInstance();
    static void DeleteInstance();

    long PerformHttpGet(std::string url) const;
private:
    CurlHandler();
    static size_t CurlWriteCallback(void *buffer, size_t size, size_t nmemb, void *userp);

    static CurlHandler* curl_handler_instance;
    CURL* curl_handle;
};