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

void StockValuation::DiscountedCashFlow(std::string symbol, float share_price, int forecast_years, float share_beta, float growth_percent){
    spdlog::info("StockValuation::DiscountedCashFlow");

    stock_data.GetFinancialData<IncomeStatement>(symbol, kIncomeStatement, income_statement);
    stock_data.GetFinancialData<BalanceSheet>(symbol, kBalanceSheet, balance_sheet);
    stock_data.GetFinancialData<CashFlow>(symbol, kCashFlow, cash_flow);

    int year = 0;
    for(auto content : income_statement.total_revenue)
        year = content.first;
}