#pragma once

#include <string>
#include "curl_handler.h"

enum FundamentalFinancialType
{
    kIncomeStatement
};

enum FinancialType
{
    kGross_profit = 0
};

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    void GetFinancial(std::string symbol,
        FinancialType financial_type);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    std::string GetFundamentalFinancial(std::string symbol,
        FundamentalFinancialType fundamental_type);
};