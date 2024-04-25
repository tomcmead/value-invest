#include "income_statement_parser.h"
#include "financial_json_parser.h"
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>
#include <vector>
#include <map>

/// @brief Parse JSON income statement object to FinancialData type
/// @param financial_data 
void IncomeStatementParser::GetFinancial(FinancialData& financial_data)
{
    spdlog::info("IncomeStatementParser::GetFinancial");
    IncomeStatementData income_statement;

    const rapidjson::Value& annual_reports = json_document["annualReports"];
    for(auto& annual_report : annual_reports.GetArray())
    {
        std::string date_str = annual_report["fiscalDateEnding"].GetString();
        int year = std::stoi(date_str.substr(0,4));

        for(int i=0; i<income_statement.financials.size(); i++)
        {
            long data = std::stol(annual_report[income_statement.financial_names[i].c_str()].GetString());
            income_statement.financials[i]->insert(std::pair<int, long>(year, data));
        }
    }

    financial_data = income_statement;
}