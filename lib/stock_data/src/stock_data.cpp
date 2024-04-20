#include <spdlog/spdlog.h>
#include <string>
#include <cstdlib>
#include "stock_data.h"
#include "curl_handler.h"

namespace
{
    const long kHttp_ok = 200;
    const std::string kAlpha_vantage_api_key_env_var = "ALPHA_VANTAGE_API_KEY";
    const std::string kIncome_statement_api = "https://www.alphavantage.co/query?function=INCOME_STATEMENT&symbol=";
}

StockData::StockData()
{
    curl_handle = CurlHandler::GetInstance();

    alpha_vantage_api_key = std::getenv(kAlpha_vantage_api_key_env_var.c_str());

    if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::StockData evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
        return;
    }

    spdlog::info("StockData::StockData Alpha Vantage API Key: {}", alpha_vantage_api_key);
}

void StockData::GetFundamentalFinancal(std::string symbol,
    FundamentalFinancalType fundamental_type)
{
    std::string api_instruction = "";
    std::string http_response = "";

    switch(fundamental_type)
    {
        case kIncomeStatement: api_instruction.append(kIncome_statement_api);
    }
    api_instruction.append(symbol);
    api_instruction.append("&apikey=" + alpha_vantage_api_key);

    try
    {
        long http_code = curl_handle->PerformHttpGet(api_instruction, http_response);
        if(http_code != kHttp_ok)
        {
            std::runtime_error("StockData::GetFundamentalFinancal " + symbol +
                " " + std::to_string(fundamental_type) + " HTTP request failed with HTTP Code: "
                + std::to_string(http_code));
        }
    }
    catch(const std::exception& e)
    {
        spdlog::critical(e.what());
        return;
    }
    spdlog::info("StockData::GetFundamentalFinancal {} {} HTTP GET request successful: {}", symbol, std::to_string(fundamental_type), http_response);
}