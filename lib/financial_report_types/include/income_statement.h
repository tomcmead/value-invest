#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>

/// @brief Income statement data structure
struct IncomeStatement : public FinancialReport
{
public:
    std::map<int, float> gross_profit;
    std::map<int, float> total_revenue;
    std::map<int, float> cost_of_revenue;
    std::map<int, float> cost_of_goods_and_services_sold;
    std::map<int, float> operating_income;
    std::map<int, float> selling_general_and_administrative;
    std::map<int, float> research_and_development;
    std::map<int, float> operating_expenses;
    std::map<int, float> investment_income_net;
    std::map<int, float> net_interest_income;
    std::map<int, float> interest_income;
    std::map<int, float> interest_expense;
    std::map<int, float> non_interest_income;
    std::map<int, float> other_non_operating_income;
    std::map<int, float> depreciation;
    std::map<int, float> depreciation_and_amortization;
    std::map<int, float> income_before_tax;
    std::map<int, float> income_tax_expense;
    std::map<int, float> interest_and_debt_expense;
    std::map<int, float> net_income_from_continuing_operations;
    std::map<int, float> comprehensive_income_net_of_tax;
    std::map<int, float> ebit;
    std::map<int, float> ebitda;
    std::map<int, float> net_income;

    const std::vector<std::pair<std::string, std::map<int, float>*>> financials = {
        std::make_pair("grossProfit", &gross_profit),
        std::make_pair("totalRevenue", &total_revenue),
        std::make_pair("costOfRevenue", &cost_of_revenue),
        std::make_pair("costofGoodsAndServicesSold", &cost_of_goods_and_services_sold),
        std::make_pair("operatingIncome", &operating_income),
        std::make_pair("sellingGeneralAndAdministrative", &selling_general_and_administrative),
        std::make_pair("researchAndDevelopment", &research_and_development),
        std::make_pair("operatingExpenses", &operating_expenses),
        std::make_pair("investmentIncomeNet", &investment_income_net),
        std::make_pair("netInterestIncome", &net_interest_income),
        std::make_pair("interestIncome", &interest_income),
        std::make_pair("interestExpense", &interest_expense),
        std::make_pair("nonInterestIncome", &non_interest_income),
        std::make_pair("otherNonOperatingIncome", &other_non_operating_income),
        std::make_pair("depreciation", &depreciation),
        std::make_pair("depreciationAndAmortization", &depreciation_and_amortization),
        std::make_pair("incomeBeforeTax", &income_before_tax),
        std::make_pair("incomeTaxExpense", &income_tax_expense),
        std::make_pair("interestAndDebtExpense", &interest_and_debt_expense),
        std::make_pair("netIncomeFromContinuingOperations", &net_income_from_continuing_operations),
        std::make_pair("comprehensiveIncomeNetOfTax", &comprehensive_income_net_of_tax),
        std::make_pair("ebit", &ebit),
        std::make_pair("ebitda", &ebitda),
        std::make_pair("netIncome", &net_income)};
};