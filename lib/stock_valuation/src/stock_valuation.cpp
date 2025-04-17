#include <spdlog/spdlog.h>
#include "stock_valuation.h"
#include "stock_data.h"
#include "balance_sheet.h"

#include <string>
#include <vector>
#include <map>
#include <cmath>

StockValuation::StockValuation()
{
    spdlog::info("StockValuation::StockValuation");
}

/// @brief Compute all steps of Discounted Cash Flow to determine
///         Per Share Value of company
/// @param symbol stock ticker
/// @param share_price current share price
/// @param forecast_year period in years the value of share price to be
/// @param share_beta company volatility metric
/// @param growth_percent estimated year-on-year growth of company
void StockValuation::DiscountedCashFlow(std::string symbol, float share_price, int forecast_years, float share_beta, float growth_percent){
    spdlog::info("StockValuation::DiscountedCashFlow");

    stock_data.GetFinancialData<IncomeStatement>(symbol, kIncomeStatement, income_statement);
    stock_data.GetFinancialData<BalanceSheet>(symbol, kBalanceSheet, balance_sheet);
    stock_data.GetFinancialData<CashFlow>(symbol, kCashFlow, cash_flow);

    int year = 0;
    for(auto content : income_statement.total_revenue)
        year = content.first;

    float forecast_free_cash = ForecastFreeCashFlow(year);
}

/// @param year the start year of forecast
/// @return float forecasted free cash flow value
float StockValuation::ForecastFreeCashFlow(int year){
    spdlog::info("StockValuation::ForecastFreeCashFlow");

    float ebit = income_statement.ebit[year];
    float depreciation_and_amortization = income_statement.depreciation_and_amortization[year];
    float change_in_working_capital = cash_flow.change_in_cash_and_cash_equivalents[year];
    float capital_expenditures = cash_flow.capital_expenditures[year];

    return ebit * (1-valuation_data::kTax_rate) + depreciation_and_amortization - change_in_working_capital - capital_expenditures;
}