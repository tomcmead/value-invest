#include "stock_data.h"
#include "error_codes.h"
#include <cstdlib>

/// @brief Configure CurlHandler and Alpha Vantage API key
StockData::StockData()
{
    spdlog::info("StockData::StockData");

    curl_handle = CurlHandler::GetInstance();
    alpha_vantage_api_key = "";

    if(std::getenv(stock_data::kAlpha_vantage_api_key_env_var.c_str()) == NULL)
    {
        spdlog::critical("StockData::StockData evironment variable '" + stock_data::kAlpha_vantage_api_key_env_var + "' is not set");
        return;
    }
    alpha_vantage_api_key = std::getenv(stock_data::kAlpha_vantage_api_key_env_var.c_str());
    spdlog::info("StockData::StockData Alpha Vantage API Key: {}", alpha_vantage_api_key);
}

/// @brief Gets raw API JSON data response as string
/// @param symbol stock ticker
/// @param report_type enum of finanical data type
/// @param api_response API JSON string response
/// @return bool success/fail
bool StockData::GetApiFundamentalData(const std::string symbol,
    FinancialReportType report_type,
    std::string& api_response)
{
    spdlog::info("StockData::GetApiFinancialData");

    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + stock_data::kAlpha_vantage_api_key_env_var + "' is not set");
        return error_codes::Fail;
    }

    std::string api_instruction = "";

    switch(report_type)
    {
        case kIncomeStatement:
            api_instruction.append(stock_data::kIncome_statement_api);
            break;
        case kBalanceSheet:
            api_instruction.append(stock_data::kBalance_sheet_api);
            break;
        case kCashFlow:
            api_instruction.append(stock_data::kCash_flow_api);
            break;
        case kEarnings:
            api_instruction.append(stock_data::kEarnings_api);
            break;
        case kSharePrice:
            api_instruction.append(stock_data::kShare_price_api);
            break;
        case kBeta:
            api_instruction.append(stock_data::kBeta_api);
            break;
        case kRiskFreeRate:
            api_instruction.append(stock_data::kRisk_free_rate_api);
            break;
        default:
            spdlog::critical("StockData::GetApiFinancialData FinancialReportType invalid");
            return error_codes::Fail;
    }
    if(report_type != kRiskFreeRate)
        api_instruction.append(symbol);
    api_instruction.append("&apikey=" + alpha_vantage_api_key);

    try
    {
        long http_code = curl_handle->PerformHttpGet(api_instruction, api_response);
        if(http_code != stock_data::kHttp_ok)
        {
            std::runtime_error("StockData::GetApiFinancialData " + symbol +
                " " + std::to_string(report_type) + " HTTP request failed with HTTP Code: "
                + std::to_string(http_code));
        }
    }
    catch(const std::exception& e)
    {
        spdlog::critical(e.what());
        return error_codes::Fail;
    }
    spdlog::info("StockData::GetApiFinancialData {} {} HTTP GET request successful", symbol, std::to_string(report_type));
    return error_codes::Success;
}

/// @brief Gets miscellaneous stock data
/// @param symbol stock ticker
/// @param data to be received
/// @param data_type miscellaneous enum of data type
/// @return bool success/fail
bool StockData::GetMiscData(const std::string symbol, float& data, stock_data::MiscData data_type)
{
    spdlog::info("StockData::GetFinancialData");
    std::string fundamental_data;

    if(data_type == stock_data::SharePrice)
    {
        if(GetApiFundamentalData(symbol, kSharePrice, fundamental_data) == error_codes::Fail)
            return error_codes::Fail;
    }
    else if(data_type == stock_data::Beta)
    {
        if(GetApiFundamentalData(symbol, kBeta, fundamental_data)  == error_codes::Fail)
            return error_codes::Fail;
    }
    else if(data_type == stock_data::RiskFreeRate)
    {
        if(GetApiFundamentalData(symbol, kRiskFreeRate, fundamental_data)  == error_codes::Fail)
            return error_codes::Fail;
    }

    if(fundamental_data.empty() == true)
    {
        spdlog::critical("StockData::ParseFundamentalData fundamental data empty");
        return error_codes::Fail;
    }

    JsonParser json_parser;

    bool parse_fail = true;
    if(data_type == stock_data::SharePrice)
        parse_fail = json_parser.ParseMiscData(fundamental_data, json_parser::SharePrice, data);
    else if(data_type == stock_data::Beta)
        parse_fail = json_parser.ParseMiscData(fundamental_data, json_parser::Beta, data);
    else if(data_type == stock_data::RiskFreeRate)
        parse_fail = json_parser.ParseMiscData(fundamental_data, json_parser::RiskFreeRate, data);

    if(parse_fail == true)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
        return error_codes::Fail;
    }
    return error_codes::Success;;
}