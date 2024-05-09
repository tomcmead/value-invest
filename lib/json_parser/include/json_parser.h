#pragma once

#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include "income_statement.h"

/// @brief Fundamental finacial base class
/// 'adapter' design pattern converts json string into FinanicalData struct
class JsonParser
{
public:
    template <typename TFinacialType>
    bool GetFinancial(std::string fundamental_json, 
        FundamentalFinancialType fundamental_type,
        TFinacialType& financial_data);
private:
    template <typename TFinacialType>
    bool ParseData(rapidjson::Document& json_document, 
        TFinacialType& financial_data);
};

/// @brief Parse JSON income statement object to FinancialData type
/// @param fundamental_json string formatted JSON
/// @param fundamental_type financial report type
/// @return bool 0=success, 1=fail
template <typename TFinacialType>
bool JsonParser::GetFinancial(std::string fundamental_json, 
        FundamentalFinancialType fundamental_type,
        TFinacialType& financial_data)
{
    spdlog::info("JsonParser::GetFinancial");

    rapidjson::Document json_document;
    financial_data.valid = false;

    if(json_document.Parse<0>(fundamental_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::JsonParser fundamental JSON data contains error");
        return 1;
    }

    return ParseData<TFinacialType>(json_document, financial_data);
}

/// @brief Parse RapidJson JSON data to FinancialType struct
/// @tparam TFinacialType 
/// @param json_document 
/// @param financial_data 
/// @return bool 0=success, 1=fail
template <typename TFinacialType>
bool JsonParser::ParseData(rapidjson::Document& json_document, 
        TFinacialType& financial_data)
{
    spdlog::info("JsonParser::ParseData");

    const rapidjson::Value& annual_reports = json_document["annualReports"];
    for(auto& annual_report : annual_reports.GetArray())
    {
        std::string date_str = annual_report["fiscalDateEnding"].GetString();
        int year = std::stoi(date_str.substr(0,4));

        for(int i=0; i<financial_data.financials.size(); i++)
        {
            long data = std::stol(annual_report[financial_data.financial_names[i].c_str()].GetString());
            financial_data.financials[i]->insert(std::pair<int, long>(year, data));
        }
    }
    financial_data.valid = true;
    return 0;
}