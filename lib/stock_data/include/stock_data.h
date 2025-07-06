#pragma once

#include "curl_handler.h"
#include "financial_report_types.h"
#include "json_parser.h"
#include <string>

namespace stock_data
{
    constexpr long kHttp_ok = 200;
    const std::string kAlpha_vantage_api_key_env_var = "ALPHA_VANTAGE_API_KEY";
    const std::string kIncome_statement_api = "https://www.alphavantage.co/query?function=INCOME_STATEMENT&symbol=";
    const std::string kBalance_sheet_api = "https://www.alphavantage.co/query?function=BALANCE_SHEET&symbol=";
    const std::string kCash_flow_api = "https://www.alphavantage.co/query?function=CASH_FLOW&symbol=";
    const std::string kEarnings_api = "https://www.alphavantage.co/query?function=EARNINGS&symbol=";
    const std::string kShare_price_api = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=";
    const std::string kBeta_api = "https://www.alphavantage.co/query?function=OVERVIEW&symbol=";
    enum MiscData {SharePrice, Beta};
}

/// @brief Get historical stock data. 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    template<typename TFinancialType>
    std::unique_ptr<TFinancialType> GetFinancialData(const std::string symbol,
        FinancialReportType report_type);
    bool GetMiscData(const std::string symbol, float& data, stock_data::MiscData data_type);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    bool GetApiFundamentalData(const std::string symbol,
        FinancialReportType report_type,
        std::string& api_response);
    template<typename TFinancialType>
    std::unique_ptr<TFinancialType> ParseFundamentalData(const std::string fundamental_data,
        FinancialReportType report_type);
};

/// @brief Generate FinancialData struct of requested symbol and financial type
/// @param symbol stock ticker
/// @param report_type enum of finanical data type
/// @return std::unique_ptr<TFinancialType> FinancialData struct
template<typename TFinancialType>
std::unique_ptr<TFinancialType> StockData::GetFinancialData(const std::string symbol,
    FinancialReportType report_type)
{
    spdlog::info("StockData::GetFinancialData");

    std::string fundamental_data;

    GetApiFundamentalData(symbol, report_type, fundamental_data);
    return ParseFundamentalData<TFinancialType>(fundamental_data, report_type);
}

/// @brief Convert raw JSON API string data to FinancialData struct
/// @param fundamental_data JSON string
/// @param report_type enum of finanical data type
/// @return std::unique_ptr<TFinancialType> FinancialData struct
template<typename TFinancialType>
std::unique_ptr<TFinancialType> StockData::ParseFundamentalData(std::string fundamental_data,
    FinancialReportType report_type)
{
    spdlog::info("StockData::ParseFundamentalData");

    if(fundamental_data.empty() == true)
    {
        spdlog::critical("StockData::ParseFundamentalData fundamental data empty");
        return nullptr;
    }

    JsonParser json_parser;
    std::unique_ptr<TFinancialType> financial_data = std::make_unique<TFinancialType>();
    financial_data = json_parser.GetFinancial<TFinancialType>(fundamental_data);
    if(financial_data == nullptr)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
        return nullptr;
    }
    return financial_data;
}