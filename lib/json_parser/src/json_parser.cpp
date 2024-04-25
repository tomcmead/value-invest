#include "json_parser.h"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <iostream>

/// @brief Parse json string to rapidjson document object
/// @param fundamental_json json string
JsonParser::JsonParser(std::string fundamental_json)
{
    spdlog::info("JsonParser::JsonParser");

    if(json_document.Parse<0>(fundamental_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::JsonParser fundamental JSON data contains error");
    }
}