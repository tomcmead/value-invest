#pragma once

#include <string>
#include "curl_handler.h"

enum FundamentalFinancalType
{
    kIncomeStatement
};

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    void GetFundamentalFinancal(std::string symbol,
        FundamentalFinancalType fundamental_type);
private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;
};