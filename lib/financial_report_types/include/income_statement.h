#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>

/// @brief Income statement data structure
struct IncomeStatement : public FinancialReport
{
public:
    std::map<int, long> gross_profit;
    std::map<int, long> total_revenue;
    std::map<int, long> cost_of_revenue;
    std::map<int, long> cost_of_goods_and_services_sold;
    std::map<int, long> operating_income;
    std::map<int, long> selling_general_and_administrative;
    std::map<int, long> research_and_development;
    std::map<int, long> operating_expenses;
    std::map<int, long> investment_income_net;
    std::map<int, long> net_interest_income;
    std::map<int, long> interest_income;
    std::map<int, long> interest_expense;
    std::map<int, long> non_interest_income;
    std::map<int, long> other_non_operating_income;
    std::map<int, long> depreciation;
    std::map<int, long> depreciation_and_amortization;
    std::map<int, long> income_before_tax;
    std::map<int, long> income_tax_expense;
    std::map<int, long> interest_and_debt_expense;
    std::map<int, long> net_income_from_continuing_operations;
    std::map<int, long> comprehensive_income_net_of_tax;
    std::map<int, long> ebit;
    std::map<int, long> ebitda;
    std::map<int, long> net_income;
    const std::vector<std::map<int, long>*> financials = {
        &gross_profit,
        &total_revenue,
        &cost_of_revenue,
        &cost_of_goods_and_services_sold,
        &operating_income,
        &selling_general_and_administrative,
        &research_and_development,
        &operating_expenses,
        &investment_income_net,
        &net_interest_income,
        &interest_income,
        &interest_expense,
        &non_interest_income,
        &other_non_operating_income,
        &depreciation,
        &depreciation_and_amortization,
        &income_before_tax,
        &income_tax_expense,
        &interest_and_debt_expense,
        &net_income_from_continuing_operations,
        &comprehensive_income_net_of_tax,
        &ebit,
        &ebitda,
        &net_income};
    const std::vector<std::string> financial_names = {
        "grossProfit",
        "totalRevenue",
        "costOfRevenue",
        "costofGoodsAndServicesSold",
        "operatingIncome",
        "sellingGeneralAndAdministrative",
        "researchAndDevelopment",
        "operatingExpenses",
        "investmentIncomeNet",
        "netInterestIncome",
        "interestIncome",
        "interestExpense",
        "nonInterestIncome",
        "otherNonOperatingIncome",
        "depreciation",
        "depreciationAndAmortization",
        "incomeBeforeTax",
        "incomeTaxExpense",
        "interestAndDebtExpense",
        "netIncomeFromContinuingOperations",
        "comprehensiveIncomeNetOfTax",
        "ebit",
        "ebitda",
        "netIncome"};
};