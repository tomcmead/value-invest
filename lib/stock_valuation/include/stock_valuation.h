#pragma once

#include "stock_data.h"
#include "balance_sheet.h"
#include <string>
#include <vector>

namespace valuation_data{
    constexpr float kInterest_rate = 0.05;
    constexpr float kTax_rate = 0.21;
    constexpr float kRisk_free_rate = 0.043;
    constexpr float kPerpetual_growth_rate = 0.025;
    constexpr float kForecast_years = 5;
    constexpr float kGrowth_years = 5;
}

class StockValuation
{
public:
    StockValuation();
    void DiscountedCashFlow(std::string symbol);
private:
    float ForecastFreeCashFlow(const int year);
    float WeightedAverageCostofCapital(const int year, const float share_price, const float share_beta, const float growth);
    float MarketCap(float share_price, const int common_share_outstanding);
    float TerminalValue(const int forecast_years, float forecast_fcf, const float wacc);
    float EnterpriseValue(const int forecast_years, const float forecast_fcf, const float wacc, float terminal_value);
    float PerShareValue(const int year, const float enterprise_value);
    float GrowthValue(const int curr_year);
    float PercentageIncrease(const float start_val, const float new_val) const;

    StockData stock_data;
    IncomeStatement income_statement;
    BalanceSheet balance_sheet;
    CashFlow cash_flow;
    Earnings earnings;
};