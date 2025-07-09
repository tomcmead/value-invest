#include "curl_handler.h"
#include <spdlog/spdlog.h>

CurlHandler* CurlHandler::curl_handler_instance = nullptr; // singleton

/// @brief Initialise cURL library
CurlHandler::CurlHandler()
{
    spdlog::info("CurlHandler::CurlHandler");

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT_MS, curl_setup::kCurl_timeout_ms);
    spdlog::info("CurlHandler::CurlHandler Configured");
}

/// @brief Cleanup cURL library data
CurlHandler::~CurlHandler()
{
    spdlog::info("CurlHandler::~CurlHandler");

    if(curl_handle != nullptr)
    {
        curl_easy_cleanup(curl_handle);
    }
    curl_global_cleanup();
    spdlog::info("CurlHandler::~CurlHandler Destroyed");
}

/// @brief Create singleton CurlHandler instance
/// @return Pointer to CurlHandler singleton instance
CurlHandler* CurlHandler::GetInstance()
{
    spdlog::info("CurlHandler::GetInstance");

    if(curl_handler_instance == nullptr)
    {
        curl_handler_instance = new CurlHandler();
    }
    return curl_handler_instance;
}

/// @brief Delete CurlHandler singleton instance
void CurlHandler::DeleteInstance()
{
    spdlog::info("CurlHandler::DeleteInstance");

    if(curl_handler_instance != nullptr)
    {
        delete curl_handler_instance;
    }
}

/// @brief Execute HTTP GET request for target URL
/// @param url target URL address
/// @param response reference to GET response string
/// @return HTTP status code
long CurlHandler::PerformHttpGet(const std::string url, std::string &response) const
{
    spdlog::info("CurlHandler::PerformHttpGet");

    long http_code = 0;
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    try
    {
        const CURLcode curl_code = curl_easy_perform(curl_handle);
        if(curl_code != CURLE_OK)
        {
            throw std::runtime_error("CurlHandler::PerformHttpGet CURL request failed with CURL Code: " + std::to_string(curl_code));
        }
    }
    catch(const std::exception &e)
    {
        spdlog::critical(e.what());
        return curl_setup::kHttp_bad_request;
    }

    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);
    spdlog::info("CurlHandler::PerformHttpGet CURL request successful");
    return http_code;
}

/// @brief Libcurl write callback for HTTP GET request
size_t CurlHandler::CurlWriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}