#pragma once

#include <string>
#include "curl_handler.h"

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    void GetIncomeStatement(std::string symbol);
private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;
};