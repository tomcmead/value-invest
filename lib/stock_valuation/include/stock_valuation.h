#pragma once

#include "stock_data.h"
#include "balance_sheet.h"
#include <string>
#include <vector>
#include <memory>

namespace valuation_data{
    constexpr float kRisk_free_rate = 0.043;
    constexpr float kForecast_years = 5;
    constexpr float kGrowth_years = 5;
    constexpr int kGrowthVariables = 9;
}

class StockValuation
{
public:
    StockValuation();
    bool DiscountedCashFlow(std::string symbol);
private:
    float ForecastFreeCashFlow(const int year, const float tax_rate);
    float WeightedAverageCostofCapital(const int year, const float share_price, const float share_beta, const float growth, const float tax_rate);
    float MarketCap(float share_price, const int common_share_outstanding) const;
    float TerminalValue(const int forecast_years, float forecast_fcf, const float wacc, const float growth);
    float EnterpriseValue(const int forecast_years, const float forecast_fcf, const float wacc, float terminal_value);
    float PerShareValue(const int year, const float enterprise_value);
    float GrowthValue(const int curr_year);
    float PercentageIncrease(const float start_val, const float new_val) const;

    StockData stock_data;
    std::unique_ptr<IncomeStatement> income_statement = std::make_unique<IncomeStatement>();
    std::unique_ptr<BalanceSheet> balance_sheet = std::make_unique<BalanceSheet>();
    std::unique_ptr<CashFlow> cash_flow = std::make_unique<CashFlow>();
    std::unique_ptr<Earnings> earnings = std::make_unique<Earnings>();
};