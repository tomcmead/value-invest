#pragma once

#include <string>
#include "curl_handler.h"
#include "json_parser.h"

/// @brief Enumerate list of fundamental financial data types
enum FundamentalFinancialType
{
    kIncomeStatement
};

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    FinancialData GetFinancialData(std::string symbol,
        FundamentalFinancialType fundamental_type);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    std::string GetApiFundamentalData(std::string symbol,
        FundamentalFinancialType fundamental_type);
    FinancialData ParseFundamentalData(std::string fundamental_data,
        FundamentalFinancialType fundamental_type);
};