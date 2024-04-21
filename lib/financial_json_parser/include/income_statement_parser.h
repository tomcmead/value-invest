#pragma once

#include "financial_json_parser.h"
#include <map>
#include <vector>

struct IncomeStatementData : private FinancialDataType
{
public:
    std::map<int, int> gross_profit;
    std::map<int, int> total_revenue;
    std::map<int, int> cost_of_revenue;
    std::map<int, int> cost_of_goods_and_services_sold;
    std::map<int, int> operating_income;
    std::map<int, int> selling_general_and_administrative;
    std::map<int, int> research_and_development;
    std::map<int, int> operating_expenses;
    std::map<int, int> investment_income_net;
    std::map<int, int> net_interest_income;
    std::map<int, int> interest_income;
    std::map<int, int> interest_expense;
    std::map<int, int> non_interest_income;
    std::map<int, int> other_non_operating_income;
    std::map<int, int> depreciation;
    std::map<int, int> depreciation_and_amortization;
    std::map<int, int> income_before_tax;
    std::map<int, int> income_tax_expense;
    std::map<int, int> interest_and_debt_expense;
    std::map<int, int> net_income_from_continuing_operations;
    std::map<int, int> comprehensive_income_net_of_tax;
    std::map<int, int> ebit;
    std::map<int, int> ebitda;
    std::map<int, int> net_income;
};

class IncomeStatementParser : public FinancialJsonParser
{
public:
    std::vector<int> GetFinancial(FinancialDataType financial_data_type) override;
private:
    using FinancialJsonParser::FinancialJsonParser; // inherit parent constructor
    IncomeStatementData* income_statement_data;
};