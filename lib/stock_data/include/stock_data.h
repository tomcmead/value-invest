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
    bool GetFinancialData(const std::string symbol,
        FinancialReportType report_type,
        TFinancialType& financial_data);
    bool GetMiscData(const std::string symbol, float& data, stock_data::MiscData data_type);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    bool GetApiFundamentalData(const std::string symbol,
        FinancialReportType report_type,
        std::string& api_response);
    template<typename TFinancialType>
    bool ParseFundamentalData(const std::string fundamental_data,
        FinancialReportType report_type,
        TFinancialType& financial_data);
};

/// @brief Generate FinancialData struct of requested symbol and financial type
/// @param symbol stock ticker
/// @param report_type enum of finanical data type
/// @param financial_data reference to FinancialData
/// @return bool 0=success, 1=fail
template<typename TFinancialType>
bool StockData::GetFinancialData(const std::string symbol,
    FinancialReportType report_type,
    TFinancialType& financial_data)
{
    spdlog::info("StockData::GetFinancialData");
    std::string fundamental_data;

    GetApiFundamentalData(symbol, report_type, fundamental_data);
    return ParseFundamentalData<TFinancialType>(fundamental_data, report_type, financial_data);
}

/// @brief Convert raw JSON API string data to FinancialData struct
/// @param fundamental_data JSON string
/// @param report_type enum of finanical data type
/// @param financial_data& reference to completed FinancialData struct
/// @return bool 0=success, 1=fail
template<typename TFinancialType>
bool StockData::ParseFundamentalData(std::string fundamental_data,
    FinancialReportType report_type,
    TFinancialType& financial_data)
{
    spdlog::info("StockData::ParseFundamentalData");

    if(fundamental_data.empty() == true)
    {
        spdlog::critical("StockData::ParseFundamentalData fundamental data empty");
        return 1;
    }

    JsonParser json_parser;
    bool parse_fail = json_parser.GetFinancial<TFinancialType>(fundamental_data, financial_data);
    if(parse_fail == true)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
    }
    return parse_fail;
}