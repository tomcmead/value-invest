#pragma once

#include <string>
#include "curl_handler.h"
#include "json_parser.h"
#include "income_statement.h"

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    void GetFinancialData(std::string symbol,
        FundamentalFinancialType fundamental_type,
        IncomeStatement& financial_data);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    std::string GetApiFundamentalData(std::string symbol,
        FundamentalFinancialType fundamental_type);
    bool ParseFundamentalData(std::string fundamental_data,
        FundamentalFinancialType fundamental_type,
        IncomeStatement& financial_data);
};