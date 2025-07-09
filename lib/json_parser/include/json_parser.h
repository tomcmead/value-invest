#pragma once

#include "income_statement.h"
#include "balance_sheet.h"
#include "cash_flow.h"
#include "earnings.h"
#include "stock_overview.h"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <string>
#include <memory>

namespace misc_type
{
    enum MiscParseData {SharePrice, RiskFreeRate};
}

/// @brief Parse JSON data using templated functions, 'adapter' design pattern converts json string into FinanicalData struct
class JsonParser
{
public:
    template <typename TFinacialReport>
    std::unique_ptr<TFinacialReport> ParseAnnualReports(const std::string financial_json);
    std::unique_ptr<StockOverview> ParseStockOverview(const std::string financial_json);
    bool ParseMiscData(const std::string financial_json,
        misc_type::MiscParseData data_type,
        float& misc_data);
};

/// @brief Parse JSON FinancialReportType object to FinancialData type
/// @tparam TFinacialType
/// @param financial_json string formatted JSON
/// @return std::unique_ptr<TFinancialType> FinancialData struct
template <typename TFinacialReport>
std::unique_ptr<TFinacialReport> JsonParser::ParseAnnualReports(const std::string financial_json)
{
    spdlog::info("JsonParser::ParseAnnualReports");

    rapidjson::Document json_document;

    if(json_document.Parse<0>(financial_json.c_str()).HasParseError())
    {
        spdlog::critical("JsonParser::ParseAnnualReports fundamental JSON data contains error");
        return nullptr;
    }

    std::unique_ptr<TFinacialReport> financial_data = std::make_unique<TFinacialReport>();
    financial_data->valid = false;

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

        for(int i=0; i<financial_data->financials.size(); i++)
        {
            std::string data_str = annual_report[financial_data->financials[i].first.c_str()].GetString();
            float data = 0;
            if(!data_str.empty() && strspn(data_str.c_str(), "-.0123456789") == data_str.size())
            {
                data = std::stof(data_str);
            }
            financial_data->financials[i].second->insert(std::pair<int, float>(year, data));
        }
    }

    return financial_data;
}