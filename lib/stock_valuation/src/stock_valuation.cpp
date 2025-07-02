#include "stock_valuation.h"
#include <spdlog/spdlog.h>
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
/// @param forecast_years period in years the value of share price to be
/// @param share_beta company volatility metric
/// @param growth_percent estimated year-on-year growth of company
void StockValuation::DiscountedCashFlow(std::string symbol, int forecast_years, float share_beta, float growth_percent){
    spdlog::info("StockValuation::DiscountedCashFlow");
	
	float share_price = 0;

    stock_data.GetFinancialData<IncomeStatement>(symbol, kIncomeStatement, income_statement);
    stock_data.GetFinancialData<BalanceSheet>(symbol, kBalanceSheet, balance_sheet);
    stock_data.GetFinancialData<CashFlow>(symbol, kCashFlow, cash_flow);
	stock_data.GetSharePrice(symbol, share_price);

    int year = 0;
    for(auto content : income_statement.total_revenue)
        year = content.first;

    float forecast_free_cash = ForecastFreeCashFlow(year);
    float wacc = WeightedAverageCostofCapital(year, share_price, share_beta, growth_percent);
    float terminal_value = TerminalValue(forecast_years, forecast_free_cash, wacc);
    float enterprise_value = EnterpriseValue(forecast_years, forecast_free_cash, wacc, terminal_value);
    float per_share_value = PerShareValue(year, enterprise_value);

    spdlog::info("Forecast Free Cash Flow {} ", forecast_free_cash);
    spdlog::info("WACC {} ", wacc);
    spdlog::info("Terminal Value {} ", terminal_value);
    spdlog::info("Enterprise Value {} ", enterprise_value);
    spdlog::info("Per Share Value {} ", per_share_value);
}

/// @brief forecast the first year of future cash flow
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

/// @brief compute WACC, the company's average after-tax cost of capital from all sources.
///         It is the average rate that a company expects to pay to finance its business.
/// @param year the start year
/// @param share_price current share price
/// @param share_beta company volatility metric
/// @param growth_percent estimated year-on-year growth of company
/// @return float Weighted Average Cost of Capital (WACC)
float StockValuation::WeightedAverageCostofCapital(int year, float share_price, float share_beta, float growth){
    spdlog::info("StockValuation::WeightedAverageCostofCapital");

    float market_cap = MarketCap(share_price, balance_sheet.common_stock_shares_outstanding[year]);
    float market_val_debt = balance_sheet.short_term_debt[year] + balance_sheet.long_term_debt[year];
    float total_enterprise_value = market_cap + market_val_debt;
    float cost_of_equity = valuation_data::kRisk_free_rate * share_beta * (growth-valuation_data::kRisk_free_rate);
    float cost_of_debt = valuation_data::kInterest_rate * (1-valuation_data::kTax_rate);

    return (market_cap/total_enterprise_value * cost_of_equity) +
            market_val_debt/total_enterprise_value * cost_of_debt * (1-valuation_data::kTax_rate);
}

float StockValuation::MarketCap(float share_price, int common_share_outstanding){
    return share_price * common_share_outstanding;
}

/// @brief estimated value beyond a forecast period into perpetuity
/// @param forecast_years period in years the value of share price to be
/// @param forecast_fcf forecasted first year free cash flow value
/// @param wacc Weighted Average Cost of Capital (WACC)
/// @return float terminal value
float StockValuation::TerminalValue(int forecast_years, float forecast_fcf, float wacc){
    spdlog::info("StockValuation::TerminalValue");

    for(int i=0; i<forecast_years; i++)
        forecast_fcf *= valuation_data::kPerpetual_growth_rate;

    return (forecast_fcf * (1 + valuation_data::kPerpetual_growth_rate)) /
        (wacc - valuation_data::kPerpetual_growth_rate);
}

/// @brief Compute companies enterprise (total) value.
///         It is theoretical price an acquirer would pay to buy the entire business.
/// @param forecast_years period in years the value of share price to be
/// @param forecast_fcf forecasted first year free cash flow value
/// @param wacc Weighted Average Cost of Capital (WACC)
/// @param terminal_value estimated value beyond a forecast period into perpetuity
/// @return float enterprise value
float StockValuation::EnterpriseValue(int forecast_years, float forecast_fcf, float wacc, float terminal_value){
    spdlog::info("StockValuation::EnterpriseValue");

    float discount_cash_flow = forecast_fcf;
    float enterprise_value = 0;

    for(int i=1; i<=forecast_years; i++){
        discount_cash_flow /= std::pow(1+wacc, i);
        enterprise_value += discount_cash_flow;
    }

    terminal_value /= std::pow(1+wacc, forecast_years);
    enterprise_value += terminal_value;

    return enterprise_value;
}

/// @brief compute estimate of the per-share cost to acquire the entire company
/// @param year the start year
/// @param enterprise_value total value
/// @return float per share value
float StockValuation::PerShareValue(int year, float enterprise_value){
    spdlog::info("StockValuation::PerShareValue");

    float net_debt = balance_sheet.short_term_debt[year] + balance_sheet.long_term_debt[year];
    float equity_value = enterprise_value - net_debt;

    return equity_value / balance_sheet.common_stock_shares_outstanding[year];
}