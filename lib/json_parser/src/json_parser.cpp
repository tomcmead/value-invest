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
    else if(data_type==json_parser::RiskFreeRate && json_document.HasMember("data"))
    {
        const rapidjson::Value& val_array = json_document["data"];
        const rapidjson::Value& val = val_array[0];
        data_str = val["value"].GetString();
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

/// @brief Parse JSON StockOverview object
/// @param financial_json string formatted JSON
/// @return std::unique_ptr<StockOverview> StockOverview struct
std::unique_ptr<StockOverview> JsonParser::ParseStockOverview(const std::string financial_json)
{
    spdlog::info("JsonParser::ParseStockOverview");

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError() && json_document.HasMember("MarketCapitalization"))
    {
        spdlog::critical("JsonParser::ParseStockOverview fundamental JSON data contains error");
        return nullptr;
    }

    std::unique_ptr<StockOverview> financial_data = std::make_unique<StockOverview>();
    financial_data->valid = false;
    std::string data_str = "";

    data_str = json_document["MarketCapitalization"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->market_capitalization = std::stof(data_str);

    data_str = json_document["EBITDA"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->ebitda = std::stof(data_str);

    data_str = json_document["PERatio"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->pe_ratio = std::stof(data_str);

    data_str = json_document["PEGRatio"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->peg_ratio = std::stof(data_str);

    data_str = json_document["BookValue"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->book_value = std::stof(data_str);

    data_str = json_document["EPS"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->eps = std::stof(data_str);

    data_str = json_document["PriceToBookRatio"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->price_to_book_ratio = std::stof(data_str);

    data_str = json_document["Beta"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->beta = std::stof(data_str);

    data_str = json_document["SharesOutstanding"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->shares_outstanding = std::stof(data_str);

    data_str = json_document["PercentInsiders"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->percent_insiders = std::stof(data_str);

    data_str = json_document["PercentInstitutions"].GetString();
    if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
        financial_data->percent_institutions = std::stof(data_str);

    return financial_data;
}