#include <json_parser.h>

/// @brief Parse RapidJson JSON data to SharePrice
/// @param financial_json std::string
/// @param data_type json_parser::MiscParseData
/// @param share_price float&
/// @return bool 0=success, 1=fail
bool JsonParser::ParseMiscData(const std::string financial_json,
        json_parser::MiscParseData data_type,
        float& share_price)
{
    spdlog::info("JsonParser::ParseMiscData");

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::ParseMiscData fundamental JSON data contains error");
        return 1;
    }

    try
    {
        std::string data_str;

        if(data_type == json_parser::SharePrice)
        {
            const rapidjson::Value& price_type = json_document["Global Quote"];
            data_str = price_type["05. price"].GetString();
        }
        else if(data_type == json_parser::Beta)
        {
            data_str = json_document["Beta"].GetString();
        }
        
        if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        {
            share_price = std::stof(data_str);
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        spdlog::critical("JsonParser::ParseMiscData {}", e.what());
        return 1;
    }

    return 0;
}