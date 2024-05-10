#include <spdlog/spdlog.h>
#include <string>
#include <cstdlib>
#include "stock_data.h"
#include "curl_handler.h"
#include "income_statement.h"
#include "financial_report.h"
#include "json_parser.h"

/// @brief Configure CurlHandler and Alpha Vantage API key
StockData::StockData()
{
    spdlog::info("StockData::StockData");

    curl_handle = CurlHandler::GetInstance();
    alpha_vantage_api_key = "";

    if(std::getenv(stock_data_api::kAlpha_vantage_api_key_env_var.c_str()) == NULL)
    {
        spdlog::critical("StockData::StockData evironment variable '" + stock_data_api::kAlpha_vantage_api_key_env_var + "' is not set");
        return;
    }
    alpha_vantage_api_key = std::getenv(stock_data_api::kAlpha_vantage_api_key_env_var.c_str());
    spdlog::info("StockData::StockData Alpha Vantage API Key: {}", alpha_vantage_api_key);
}

/// @brief Gets raw API JSON data response as string
/// @param symbol stock ticker
/// @param report_type enum of finanical data type
/// @param http_response API JSON string response
/// @return bool 0=success, 1=fail
bool StockData::GetApiFundamentalData(std::string symbol,
    FinancialReportType report_type,
    std::string& api_response)
{
    spdlog::info("StockData::GetApiFinancialData");

    std::string api_instruction = "";

    switch(report_type)
    {
        case kIncomeStatement:
            api_instruction.append(stock_data_api::kIncome_statement_api);
            break;
    }
    api_instruction.append(symbol);
    api_instruction.append("&apikey=" + alpha_vantage_api_key);

    try
    {
        long http_code = curl_handle->PerformHttpGet(api_instruction, api_response);
        if(http_code != stock_data_api::kHttp_ok)
        {
            std::runtime_error("StockData::GetApiFinancialData " + symbol +
                " " + std::to_string(report_type) + " HTTP request failed with HTTP Code: "
                + std::to_string(http_code));
        }
    }
    catch(const std::exception& e)
    {
        spdlog::critical(e.what());
        return 1;
    }
    spdlog::info("StockData::GetApiFinancialData {} {} HTTP GET request successful", symbol, std::to_string(report_type));
    return 0;
}