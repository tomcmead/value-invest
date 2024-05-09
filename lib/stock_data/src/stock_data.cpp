#include <spdlog/spdlog.h>
#include <string>
#include <cstdlib>
#include <memory>
#include "stock_data.h"
#include "curl_handler.h"
#include "income_statement.h"
#include "json_parser.h"

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
/// @param financial_data reference to FinancialData
/// @return bool 0=success, 1=fail
void StockData::GetFinancialData(std::string symbol,
    FundamentalFinancialType fundamental_type,
    IncomeStatement& financial_data)
{
    spdlog::info("StockData::GetFinancialData");

    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
    }

    std::string fundamental_data = GetApiFundamentalData(symbol, fundamental_type);
    ParseFundamentalData(fundamental_data, fundamental_type, financial_data);
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
/// @param financial_data& reference to completed FinancialData struct
/// @return bool 0=success, 1=fail
bool StockData::ParseFundamentalData(std::string fundamental_data,
    FundamentalFinancialType fundamental_type,
    IncomeStatement& financial_data)
{
    spdlog::info("StockData::ParseFundamentalData");

    // std::unique_ptr<JsonParser> json_parser(new JsonParser);
    // bool parse_fail = json_parser->GetFinancial(fundamental_data, fundamental_type, financial_data);
    JsonParser json_parser;
    bool parse_fail = json_parser.GetFinancial<IncomeStatement>(fundamental_data, fundamental_type, financial_data);
    if(parse_fail == true)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
    }
    return parse_fail;
}