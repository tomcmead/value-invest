#include "income_statement_parser.h"
#include "financial_json_parser.h"
#include <spdlog/spdlog.h>
#include <rapidjson/document.h>
#include <vector>
#include <map>

void IncomeStatementParser::GetFinancial(FinancialData& financial_data)
{
    spdlog::info("IncomeStatementParser::GetFinancial");
    IncomeStatementData income_statement;

    const rapidjson::Value& annual_reports = json_document["annualReports"];
    for(auto& annual_report : annual_reports.GetArray())
    {
        std::string date_str = annual_report["fiscalDateEnding"].GetString();
        int year = std::stoi(date_str.substr(0,4));

        int gross_profit = std::stoi(annual_report["grossProfit"].GetString());
        income_statement.gross_profit.insert(std::pair<int,int>(year, gross_profit));
    }

    financial_data = income_statement;
}