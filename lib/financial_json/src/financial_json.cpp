#include "financial_json.h"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>

/// @brief Parse json string to rapidjson document object
/// @param fundamental_json json string
FinancialJson::FinancialJson(std::string fundamental_json)
{
    json_document = new rapidjson::Document;
    if(json_document->Parse<0>(fundamental_json.c_str()).HasParseError())
    {
        spdlog::critical("FinancialJson::FinancialJson fundamental JSON data contains error");
    }
}

/// @brief Clean-up
FinancialJson::~FinancialJson()
{
    delete json_document;
}