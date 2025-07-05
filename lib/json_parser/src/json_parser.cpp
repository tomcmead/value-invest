#include <json_parser.h>

/// @brief Parse RapidJson JSON data to SharePrice
/// @param financial_json 
/// @param share_price 
/// @return bool 0=success, 1=fail
bool JsonParser::ParseSharePriceData(const std::string financial_json, 
        float& share_price)
{
    spdlog::info("JsonParser::ParseSharePriceData");

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::ParseSharePriceData fundamental JSON data contains error");
        return 1;
    }

    try
    {
        const rapidjson::Value& price_type = json_document["Global Quote"];
        const std::string data_str = price_type["05. price"].GetString();
        if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        {
            share_price = std::stof(data_str);
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        spdlog::critical("JsonParser::ParseSharePriceData {}", e.what());
        return 1;
    }

    return 0;
}

/// @brief Parse RapidJson JSON data to Beta
/// @param financial_json
/// @param beta
/// @return bool 0=success, 1=fail
bool JsonParser::ParseBetaData(const std::string financial_json, 
        float& beta)
{
    spdlog::info("JsonParser::ParseBetaData");
    spdlog::info("StockData::ParseBetaData {}", financial_json);

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::ParseBetaData fundamental JSON data contains error");
        return 1;
    }

    try
    {
        const std::string data_str = json_document["Beta"].GetString();
        if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        {
            beta = std::stof(data_str);
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        spdlog::critical("JsonParser::ParseBetaData {}", e.what());
        return 1;
    }

    return 0;
}