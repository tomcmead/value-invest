#pragma once

#include <string>
#include "curl_handler.h"
#include "json_parser.h"
#include "income_statement.h"

namespace stock_data_api
{
    const long kHttp_ok = 200;
    const std::string kAlpha_vantage_api_key_env_var = "ALPHA_VANTAGE_API_KEY";
    const std::string kIncome_statement_api = "https://www.alphavantage.co/query?function=INCOME_STATEMENT&symbol=";
}

/// @brief Get historical stock data
/// 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    template<typename TFinancialType>
    void GetFinancialData(std::string symbol,
        FundamentalFinancialType fundamental_type,
        TFinancialType& financial_data);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    std::string GetApiFundamentalData(std::string symbol,
        FundamentalFinancialType fundamental_type);
    template<typename TFinancialType>
    bool ParseFundamentalData(std::string fundamental_data,
        FundamentalFinancialType fundamental_type,
        TFinancialType& financial_data);
};

/// @brief Generate FinancialData struct of requested symbol and financial type
/// @param symbol stock ticker
/// @param fundamental_type enum of finanical data type
/// @param financial_data reference to FinancialData
/// @return bool 0=success, 1=fail
template<typename TFinancialType>
void StockData::GetFinancialData(std::string symbol,
    FundamentalFinancialType fundamental_type,
    TFinancialType& financial_data)
{
    spdlog::info("StockData::GetFinancialData");

    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + stock_data_api::kAlpha_vantage_api_key_env_var + "' is not set");
    }

    std::string fundamental_data = GetApiFundamentalData(symbol, fundamental_type);
    ParseFundamentalData<TFinancialType>(fundamental_data, fundamental_type, financial_data);
}

/// @brief Convert raw JSON API string data to FinancialData struct
/// @param fundamental_data JSON string
/// @param fundamental_type enum of finanical data type
/// @param financial_data& reference to completed FinancialData struct
/// @return bool 0=success, 1=fail
template<typename TFinancialType>
bool StockData::ParseFundamentalData(std::string fundamental_data,
    FundamentalFinancialType fundamental_type,
    TFinancialType& financial_data)
{
    spdlog::info("StockData::ParseFundamentalData");

    // std::unique_ptr<JsonParser> json_parser(new JsonParser);
    // bool parse_fail = json_parser->GetFinancial(fundamental_data, fundamental_type, financial_data);
    JsonParser json_parser;
    bool parse_fail = json_parser.GetFinancial<TFinancialType>(fundamental_data, fundamental_type, financial_data);
    if(parse_fail == true)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
    }
    return parse_fail;
}