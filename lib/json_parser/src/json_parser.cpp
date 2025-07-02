#include <json_parser.h>

/// @brief Parse RapidJson JSON data to SharePrice struct
/// @param json_document 
/// @param share_price 
/// @return bool 0=success, 1=fail
bool JsonParser::ParseSharePriceData(std::string financial_json, 
        float& share_price)
{
    spdlog::info("JsonParser::ParseSharePriceData");
	
	rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::JsonParser fundamental JSON data contains error");
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