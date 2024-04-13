#include <curl/curl.h>
#include "curl_handler.h"

CurlHandler* CurlHandler::curl_handler_instance = nullptr; // singleton

/// @brief Initialise cURL library
CurlHandler::CurlHandler()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_handle = curl_easy_init();
}

/// @brief Cleanup cURL library data
CurlHandler::~CurlHandler()
{
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
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