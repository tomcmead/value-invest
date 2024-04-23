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

/// @brief Configure CurlHandler, FinancialJson & API key
StockData::StockData()
{
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

FinancialData StockData::GetFinancialData(std::string symbol,
    FundamentalFinancialType fundamental_type)
{
    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
    }

    std::string fundamental_data = GetApiFundamentalData(symbol, fundamental_type);
    FinancialData financial_data = ParseFundamentalData(fundamental_data, fundamental_type);
    return financial_data;
}

std::string StockData::GetApiFundamentalData(std::string symbol,
    FundamentalFinancialType fundamental_type)
{
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

FinancialData StockData::ParseFundamentalData(std::string fundamental_data,
    FundamentalFinancialType fundamental_type)
{
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