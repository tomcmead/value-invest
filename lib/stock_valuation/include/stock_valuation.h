#pragma once

#include "stock_data.h"
#include "balance_sheet.h"
#include <string>
#include <vector>

namespace valuation_data{
    const float kInterest_rate = 0.05;
    const float kTax_rate = 0.21;
    const float kRisk_free_rate = 0.043;
    const float kPerpetual_growth_rate = 0.025;
}

class StockValuation
{
public:
    StockValuation();
    void DiscountedCashFlow(std::string symbol, float share_price, int forecast_years, float share_beta, float growth_percent);
private:
    float ForecastFreeCashFlow(int year);
    float WeightedAverageCostofCapital(int year, float share_price, float share_beta, float growth);
    float MarketCap(float share_price, int common_share_outstanding);
    float TerminalValue(int forecast_years, float forecast_fcf, float wacc);

    StockData stock_data;
    IncomeStatement income_statement;
    BalanceSheet balance_sheet;
    CashFlow cash_flow;
};