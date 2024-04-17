#include <spdlog/spdlog.h>
#include <string>
#include <cstdlib>
#include "stock_data.h"
#include "curl_handler.h"

namespace
{
    const std::string kAlpha_vantage_api_key_env_var = "ALPHA_VANTAGE_API_KEY";
}

StockData::StockData()
{
    curl_handle = CurlHandler::GetInstance();

    alpha_vantage_api_key = std::stoi(std::getenv(kAlpha_vantage_api_key_env_var.c_str()));

    if(!alpha_vantage_api_key)
    {
        spdlog::critical("StockData::StockData evironment variable '" + kAlpha_vantage_api_key_env_var + "' is not set");
        return;
    }

    spdlog::info("Alpha Vantage API Key: {0:d}", alpha_vantage_api_key);
}