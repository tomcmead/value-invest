#include "stock_data.h"
#include <cstdlib>

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
	
	 if(alpha_vantage_api_key.empty() == true)
    {
        spdlog::critical("StockData::GetFinancial evironment variable '" + stock_data_api::kAlpha_vantage_api_key_env_var + "' is not set");
        return 1;
    }

    std::string api_instruction = "";

    switch(report_type)
    {
        case kIncomeStatement:
            api_instruction.append(stock_data_api::kIncome_statement_api);
            break;
        case kBalanceSheet:
            api_instruction.append(stock_data_api::kBalance_sheet_api);
            break;
        case kCashFlow:
            api_instruction.append(stock_data_api::kCash_flow_api);
            break;
        case kEarnings:
            api_instruction.append(stock_data_api::kEarnings_api);
            break;
		case kSharePrice:
			api_instruction.append(stock_data_api::kShare_price_api);
			break;
		case kBeta:
			api_instruction.append(stock_data_api::kBeta_api);
			break;
        default:
            spdlog::critical("StockData::GetApiFinancialData FinancialReportType invalid");
            return 1;
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

/// @brief Gets miscellaneous stock data
/// @param symbol stock ticker
/// @param data to be received
/// @param miscellaneous enum of data type
/// @return bool 0=success, 1=fail
bool StockData::GetMiscData(std::string symbol, float& data, stock_data_api::MiscData data_type)
{
	spdlog::info("StockData::GetFinancialData");
    std::string fundamental_data;

    GetApiFundamentalData(symbol, kSharePrice, fundamental_data);
	
	if(fundamental_data.empty() == true)
    {
        spdlog::critical("StockData::ParseFundamentalData fundamental data empty");
        return 1;
    }

    JsonParser json_parser;
	bool parse_fail = true;
	switch(data_type){
		case stock_data_api::SharePrice:
			parse_fail = json_parser.ParseSharePriceData(fundamental_data, data);
			break;
		case stock_data_api::Beta:
			parse_fail = json_parser.ParseSharePriceData(fundamental_data, data);
	}

    if(parse_fail == true)
    {
        spdlog::critical("StockData::ParseFundamentalData JSON parsing failed");
    }
	return 0;
}