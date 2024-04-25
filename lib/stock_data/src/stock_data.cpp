#include <spdlog/spdlog.h>
#include <string>
#include <cstdlib>
#include <memory>
#include "stock_data.h"
#include "curl_handler.h"
#include "income_statement_parser.h"

namespace
{
    const long kHttp_ok = 200;
    const std::string kAlpha_vantage_api_key_env_var = "ALPHA_VANTAGE_API_KEY";
    const std::string kIncome_statement_api = "https://www.alphavantage.co/query?function=INCOME_STATEMENT&symbol=";
}

/// @brief Configure CurlHandler and Alpha Vantage API key
StockData::StockData()
{
    spdlog::info("StockData::StockData");

    curl_handle = CurlHandler::GetInstance();
    alpha_vantage_api_key = "";

    if(std::getenv(kAlpha_vantage_api_key_env_var.c_str()) == NULL)
    {
        spdlog::critical("StockData::StockData evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
        return;
    }
    alpha_vantage_api_key = std::getenv(kAlpha_vantage_api_key_env_var.c_str());
    spdlog::info("StockData::StockData Alpha Vantage API Key: {}", alpha_vantage_api_key);
}

/// @brief Generate FinancialData struct of requested symbol and financial type
/// @param symbol stock ticker
/// @param fundamental_type enum of finanical data type
/// @return financial data struct
FinancialData StockData::GetFinancialData(std::string symbol,
    FundamentalFinancialType fundamental_type)
{
    spdlog::info("StockData::GetFinancialData");

    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
    }

    std::string fundamental_data = GetApiFundamentalData(symbol, fundamental_type);
    FinancialData financial_data = ParseFundamentalData(fundamental_data, fundamental_type);
    return financial_data;
}

/// @brief Gets raw API JSON data response as string
/// @param symbol stock ticker
/// @param fundamental_type enum of finanical data type
/// @return API JSON string response
std::string StockData::GetApiFundamentalData(std::string symbol,
    FundamentalFinancialType fundamental_type)
{
    spdlog::info("StockData::GetApiFinancialData");

    std::string api_instruction = "";
    std::string http_response = "";

    switch(fundamental_type)
    {
        case kIncomeStatement:
            api_instruction.append(kIncome_statement_api);
            break;
    }
    api_instruction.append(symbol);
    api_instruction.append("&apikey=" + alpha_vantage_api_key);

    try
    {
        long http_code = curl_handle->PerformHttpGet(api_instruction, http_response);
        if(http_code != kHttp_ok)
        {
            std::runtime_error("StockData::GetApiFinancialData " + symbol +
                " " + std::to_string(fundamental_type) + " HTTP request failed with HTTP Code: "
                + std::to_string(http_code));
        }
    }
    catch(const std::exception& e)
    {
        spdlog::critical(e.what());
        return "";
    }
    spdlog::info("StockData::GetApiFinancialData {} {} HTTP GET request successful", symbol, std::to_string(fundamental_type));
    return http_response;
}

/// @brief Convert raw JSON API string data to FinancialData struct
/// @param fundamental_data JSON string
/// @param fundamental_type enum of finanical data type
/// @return FinancialData struct
FinancialData StockData::ParseFundamentalData(std::string fundamental_data,
    FundamentalFinancialType fundamental_type)
{
    spdlog::info("StockData::ParseFundamentalData");

    IncomeStatementData data;
    switch(fundamental_type)
    {
        case kIncomeStatement:
        {
            std::unique_ptr<IncomeStatementParser> income_statement_parser(new IncomeStatementParser(fundamental_data));
            IncomeStatementData income_statement_data;
            income_statement_parser->GetFinancial(income_statement_data);
            return income_statement_data;
        }
    }
    return data;
}