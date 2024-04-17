#include <curl/curl.h>
#include <spdlog/spdlog.h>
#include <string>
#include "curl_handler.h"

namespace
{
    const int kHttp_ok = 200;
    const int kHttp_bad_request = 300;
}

CurlHandler* CurlHandler::curl_handler_instance = nullptr; // singleton

/// @brief Initialise cURL library
CurlHandler::CurlHandler()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    spdlog::info("CurlHandler Configured");
}

/// @brief Cleanup cURL library data
CurlHandler::~CurlHandler()
{
    if(curl_handle != nullptr)
    {
        curl_easy_cleanup(curl_handle);
    }
    curl_global_cleanup();
    spdlog::info("CurlHandler Destroyed");
}

/// @brief Create singleton CurlHandler instance
/// @return Pointer to CurlHandler singleton instance
CurlHandler* CurlHandler::GetInstance()
{
    if(curl_handler_instance == nullptr)
    {
        curl_handler_instance = new CurlHandler();
    }
    return curl_handler_instance;
}

/// @brief Delete CurlHandler singleton instance
void CurlHandler::DeleteInstance()
{
    if(curl_handler_instance != nullptr)
    {
        delete curl_handler_instance;
    }
}

/// @brief Execute HTTP GET request for target URL
/// @param url target URL address
/// @return HTTP status code
long CurlHandler::PerformHttpGet(std::string url) const
{
    long http_code = 0;
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

    try
    {
        CURLcode curl_code = curl_easy_perform(curl_handle);
        if(curl_code != CURLE_OK)
        {
            throw std::runtime_error("CurlHandler::PerformHttpGet CURL request failed with CURL Code: " + std::to_string(curl_code));
        }
    }
    catch(const std::exception &ex)
    {
        spdlog::critical(ex.what());
        return kHttp_bad_request;
    }

    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);
    spdlog::info("CurlHandler::PerformHttpGet HTTP GET request successful");
    return http_code;
}

/// @brief Empty libcurl callback for HTTP GET request
size_t CurlHandler::CurlWriteCallback(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}