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

    spdlog::info("StockData::StockData Alpha Vantage API Key: {}", alpha_vantage_api_key.c_str());
}

void StockData::GetIncomeStatement(std::string symbol)
{
    try
    {
        std::string api_instruction = kIncome_statement_api + symbol + "&apikey=" + alpha_vantage_api_key;
        long http_code = curl_handle->PerformHttpGet(api_instruction);
        if(http_code != kHttp_ok)
        {
            std::runtime_error("StockData::GetIncomeStatement HTTP request failed with HTTP Code: " + std::to_string(http_code));
        }
    }
    catch(const std::exception& e)
    {
        spdlog::critical(e.what());
        return;
    }
    spdlog::info("StockData::GetIncomeStatement HTTP GET request successful");
}