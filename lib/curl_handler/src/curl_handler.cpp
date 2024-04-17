#include <curl/curl.h>
#include <spdlog/spdlog.h>
#include <string>
#include "curl_handler.h"

CurlHandler* CurlHandler::curl_handler_instance = nullptr; // singleton

namespace
{
    const std::string kRemote_endpoint_url = "www.google.com";
}

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

CURLcode CurlHandler::PerformHttpGet()
{
    curl_easy_setopt(curl_handle, CURLOPT_URL, kRemote_endpoint_url.c_str());
    CURLcode res = curl_easy_perform(curl_handle);
    spdlog::info("HTTP Status code: {0:d}", static_cast<int>(res));
    return res;
}

size_t CurlHandler::CurlWriteCallback(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}