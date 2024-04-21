#include "financial_json_parser.h"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>

/// @brief Parse json string to rapidjson document object
/// @param fundamental_json json string
FinancialJsonParser::FinancialJsonParser(std::string fundamental_json)
{
    json_document = new rapidjson::Document;
    if(json_document->Parse<0>(fundamental_json.c_str()).HasParseError())
    {
        spdlog::critical("FinancialJson::FinancialJson fundamental JSON data contains error");
    }
}

/// @brief Clean-up
FinancialJsonParser::~FinancialJsonParser()
{
    delete json_document;
}