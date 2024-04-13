#pragma once

#include <curl/curl.h>

/// @brief cURL library API handler.
/// 'Singeleton' and 'Facade' design patterns
class CurlHandler
{
public:
    CurlHandler(CurlHandler const&) = delete;
    CurlHandler& operator=(CurlHandler const&) = delete;
    virtual ~CurlHandler();

    static CurlHandler* GetInstance();
    static void DeleteInstance();
private:
    CurlHandler();
    static CurlHandler* curl_handler_instance;
    CURL* curl_handle;
};