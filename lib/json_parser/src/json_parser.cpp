#include "json_parser.h"
#include "error_codes.h"

/// @brief Parse RapidJson JSON data to SharePrice
/// @param financial_json std::string
/// @param data_type json_parser::MiscParseData
/// @param misc_data float& for misc_data result
/// @return bool success/fail
bool JsonParser::ParseMiscData(const std::string financial_json,
        json_parser::MiscParseData data_type,
        float& misc_data)
{
    spdlog::info("JsonParser::ParseMiscData");

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::ParseMiscData fundamental JSON data contains error");
        return error_codes::Fail;
    }

    std::string data_str;

    if(data_type==json_parser::SharePrice && json_document.HasMember("Global Quote"))
    {
        const rapidjson::Value& price_type = json_document["Global Quote"];
        data_str = price_type["05. price"].GetString();
    }
    else if(data_type==json_parser::Beta && json_document.HasMember("Beta"))
    {
        data_str = json_document["Beta"].GetString();
    }
    else
    {
        spdlog::critical("JsonParser::ParseMiscData JSON data missing target member");
        return error_codes::Fail;
    }
    
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
    {
        misc_data = std::stof(data_str);
    }
    else
    {
        spdlog::critical("JsonParser::ParseMiscData JSON member invalid type");
        return error_codes::Fail;
    }

    return error_codes::Success;
}