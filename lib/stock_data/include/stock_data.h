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
    const std::string kStock_overview_api = "https://www.alphavantage.co/query?function=OVERVIEW&symbol=";
    const std::string kShare_price_api = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=";
    const std::string kRisk_free_rate_api = "https://www.alphavantage.co/query?function=TREASURY_YIELD&interval=daily&maturity=10year";
    enum MiscData {SharePrice, RiskFreeRate};
}

/// @brief Get historical stock data. 'facade' for 'Alpha Vantage API' financial data
class StockData
{
public:
    StockData();
    template<typename TFinancialType>
    std::unique_ptr<TFinancialType> GetAnnualReportData(const std::string symbol,
        FinancialReportType report_type);
    std::unique_ptr<StockOverview> GetStockOverviewData(const std::string symbol);
    bool GetMiscData(const std::string symbol, float& data, stock_data::MiscData data_type);

private:
    CurlHandler* curl_handle;
    std::string alpha_vantage_api_key;

    bool GetApiFundamentalData(const std::string symbol,
        FinancialReportType report_type,
        std::string& api_response);
};

/// @brief Get and convert raw JSON API string data to FinancialData struct
/// @param symbol ticker string
/// @param report_type enum of finanical data type
/// @return std::unique_ptr<TFinancialType> FinancialData struct
template<typename TFinancialType>
std::unique_ptr<TFinancialType> StockData::GetAnnualReportData(const std::string symbol,
    FinancialReportType report_type)
{
    spdlog::info("StockData::GetAnnualReportData");

    std::string fundamental_data;
    GetApiFundamentalData(symbol, report_type, fundamental_data);

    if(fundamental_data.empty() == true)
    {
        spdlog::critical("StockData::GetAnnualReportData fundamental data empty");
        return nullptr;
    }

    JsonParser json_parser;
    std::unique_ptr<TFinancialType> financial_data = std::make_unique<TFinancialType>();
    financial_data = json_parser.ParseAnnualReports<TFinancialType>(fundamental_data);

    if(financial_data == nullptr)
    {
        spdlog::critical("StockData::GetAnnualReportData JSON parsing failed");
        return nullptr;
    }
    return financial_data;
}