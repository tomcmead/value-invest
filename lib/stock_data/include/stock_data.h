#pragma once

#include "curl_handler.h"

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
private:
    CurlHandler* curl_handle;
    int alpha_vantage_api_key;
};