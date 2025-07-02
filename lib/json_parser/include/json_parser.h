#pragma once

#include "income_statement.h"
#include "balance_sheet.h"
#include "cash_flow.h"
#include "earnings.h"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <string>

/// @brief Parse JSON data using templated functions, 'adapter' design pattern converts json string into FinanicalData struct
class JsonParser
{
public:
    template <typename TFinacialReport>
    bool GetFinancial(std::string financial_json, 
        TFinacialReport& financial_data);
	bool ParseSharePriceData(std::string financial_json, 
        float& share_price);
private:
    template <typename TFinacialReport>
    bool ParseData(rapidjson::Document& json_document, 
        TFinacialReport& financial_data);
};

/// @brief Parse JSON FinancialReportType object to FinancialData type
/// @tparam TFinacialType 
/// @param financial_json string formatted JSON
/// @param financial_data template function of FinancialType struct
/// @return bool 0=success, 1=fail
template <typename TFinacialReport>
bool JsonParser::GetFinancial(std::string financial_json, 
        TFinacialReport& financial_data)
{
    spdlog::info("JsonParser::GetFinancial");

    rapidjson::Document json_document;
    financial_data.valid = false;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::JsonParser fundamental JSON data contains error");
        return 1;
    }

    return ParseData<TFinacialReport>(json_document, financial_data);
}

/// @brief Parse RapidJson JSON data to FinancialType struct
/// @tparam TFinacialType 
/// @param json_document 
/// @param financial_data 
/// @return bool 0=success, 1=fail
template <typename TFinacialReport>
bool JsonParser::ParseData(rapidjson::Document& json_document, 
        TFinacialReport& financial_data)
{
    spdlog::info("JsonParser::ParseData");

    try
    {
        rapidjson::Value& annual_reports = json_document["annualEarnings"];

        rapidjson::Value::ConstMemberIterator itr = json_document.FindMember("annualReports");
        if (itr != json_document.MemberEnd())
        {
            annual_reports = json_document["annualReports"];
        }

        for(auto& annual_report : annual_reports.GetArray())
        {
            std::string date_str = annual_report["fiscalDateEnding"].GetString();
            int year = std::stoi(date_str.substr(0,4));

            for(int i=0; i<financial_data.financials.size(); i++)
            {
                std::string data_str = annual_report[financial_data.financials[i].first.c_str()].GetString();
                float data = 0;
                if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
                {
                    data = std::stof(data_str);
                }
                financial_data.financials[i].second->insert(std::pair<int, float>(year, data));
            }
        }

        financial_data.valid = true;
    }
    catch(const std::exception& e)
    {
        spdlog::critical("JsonParser::ParseData {}", e.what());
        return 1;
    }

    return 0;
}