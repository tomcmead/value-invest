#include "stock_valuation.h"
#include "error_codes.h"
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
/// @return bool success/fail
bool StockValuation::DiscountedCashFlow(const std::string symbol){
    spdlog::info("StockValuation::DiscountedCashFlow");

    float share_price = 0;
    float risk_free_rate = 0;

    income_statement = stock_data.GetAnnualReportData<IncomeStatement>(symbol, kIncomeStatement);
    balance_sheet = stock_data.GetAnnualReportData<BalanceSheet>(symbol, kBalanceSheet);
    cash_flow = stock_data.GetAnnualReportData<CashFlow>(symbol, kCashFlow);
    earnings = stock_data.GetAnnualReportData<Earnings>(symbol, kEarnings);
    stock_overview = stock_data.GetStockOverviewData(symbol);
    stock_data.GetMiscData(symbol, share_price, stock_data::SharePrice);
    stock_data.GetMiscData(symbol, risk_free_rate, stock_data::RiskFreeRate);
    risk_free_rate /= 100;

    if(income_statement==nullptr || balance_sheet==nullptr || cash_flow==nullptr || earnings==nullptr || stock_overview==nullptr){
         spdlog::critical("StockValuation::DiscountedCashFlow Financial Document NULL");
         return error_codes::Fail;
    }

    int year = 0;
    for(auto content : income_statement->total_revenue)
        year = content.first;

    const float effective_tax_rate = income_statement->income_tax_expense[year] / income_statement->income_before_tax[year];
    const float growth = GrowthValue(year);
    const float forecast_free_cash = ForecastFreeCashFlow(year, effective_tax_rate);
    const float wacc = WeightedAverageCostofCapital(year, share_price, growth, effective_tax_rate, risk_free_rate);
    const float terminal_value = TerminalValue(valuation_data::kForecast_years, forecast_free_cash, wacc, growth);
    const float enterprise_value = EnterpriseValue(valuation_data::kForecast_years, forecast_free_cash, wacc, terminal_value);
    const float per_share_value = PerShareValue(year, enterprise_value);

    spdlog::info("Growth: {}", growth);
    spdlog::info("Share Price: {}", share_price);
    spdlog::info("Forecast Free Cash Flow {} ", forecast_free_cash);
    spdlog::info("WACC {} ", wacc);
    spdlog::info("Terminal Value {} ", terminal_value);
    spdlog::info("Enterprise Value {} ", enterprise_value);
    spdlog::info("Per Share Value {} ", per_share_value);

    return error_codes::Success;
}

/// @brief forecast the first year of future cash flow
/// @param year the start year of forecast
/// @param tax_rate company average tax rate
/// @return float forecasted free cash flow value
float StockValuation::ForecastFreeCashFlow(const int year, const float tax_rate){
    spdlog::info("StockValuation::ForecastFreeCashFlow");

    float ebit = income_statement->ebit[year];
    float depreciation_and_amortization = income_statement->depreciation_and_amortization[year];
    float change_in_working_capital = cash_flow->change_in_cash_and_cash_equivalents[year];
    float capital_expenditures = cash_flow->capital_expenditures[year];

    return ebit * (1-tax_rate) + depreciation_and_amortization - change_in_working_capital - capital_expenditures;
}

/// @brief compute WACC, the company's average after-tax cost of capital from all sources.
///         It is the average rate that a company expects to pay to finance its business.
/// @param year the start year
/// @param share_price current share price
/// @param growth estimated year-on-year growth of company
/// @param tax_rate company average tax rate
/// @param risk_free_rate yield on a 10-year U.S. Treasury bond
/// @return float Weighted Average Cost of Capital (WACC)
float StockValuation::WeightedAverageCostofCapital(const int year, const float share_price, const float growth, const float tax_rate, const float risk_free_rate){
    spdlog::info("StockValuation::WeightedAverageCostofCapital");

    float market_cap = stock_overview->market_capitalization;
    float market_val_debt = balance_sheet->short_long_term_debt_total[year];
    float total_enterprise_value = market_cap + market_val_debt;
    float cost_of_equity = risk_free_rate * stock_overview->beta * (growth-risk_free_rate);
    float interest_rate = income_statement->interest_expense[year] / balance_sheet->short_long_term_debt_total[year];
    float cost_of_debt = interest_rate * (1-tax_rate);

    return ((market_cap/total_enterprise_value) * cost_of_equity) +
            ((market_val_debt/total_enterprise_value) * cost_of_debt * (1-tax_rate));
}

/// @brief estimated value beyond a forecast period into perpetuity
/// @param forecast_years period in years the value of share price to be
/// @param forecast_fcf forecasted first year free cash flow value
/// @param wacc Weighted Average Cost of Capital (WACC)
/// @param growth estimate company growth YoY
/// @return float terminal value
float StockValuation::TerminalValue(const int forecast_years, float forecast_fcf, const float wacc, const float growth){
    spdlog::info("StockValuation::TerminalValue");

    for(int i=0; i<forecast_years; i++)
        forecast_fcf *= (1+growth);

    return (forecast_fcf * (1 + growth)) /
        (wacc - growth);
}

/// @brief Compute companies enterprise (total) value.
///         It is theoretical price an acquirer would pay to buy the entire business.
/// @param forecast_years period in years the value of share price to be
/// @param forecast_fcf forecasted first year free cash flow value
/// @param wacc Weighted Average Cost of Capital (WACC)
/// @param terminal_value estimated value beyond a forecast period into perpetuity
/// @return float enterprise value
float StockValuation::EnterpriseValue(const int forecast_years, const float forecast_fcf, const float wacc, float terminal_value){
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
float StockValuation::PerShareValue(const int year, const float enterprise_value){
    spdlog::info("StockValuation::PerShareValue");

    float net_debt = balance_sheet->short_term_debt[year] + balance_sheet->long_term_debt[year];
    float equity_value = enterprise_value - net_debt;

    return equity_value / balance_sheet->common_stock_shares_outstanding[year];
}

/// @brief compute estimate of the company growth
/// @param curr_year int current year
/// @return float per share value
float StockValuation::GrowthValue(const int curr_year){
    spdlog::info("StockValuation::GrowthValue");

    float growth = 0;
    const int historical_years = income_statement->total_revenue.size() < valuation_data::kGrowth_years ? 
                                    income_statement->total_revenue.size() : valuation_data::kGrowth_years;

    for(int year=curr_year-historical_years+1; year<curr_year; year++)
    {
        growth += PercentageIncrease(income_statement->total_revenue[year-1], income_statement->total_revenue[year]);
        growth += PercentageIncrease(income_statement->gross_profit[year-1], income_statement->gross_profit[year]);
        growth += PercentageIncrease(income_statement->net_income[year-1], income_statement->net_income[year]);
        growth += PercentageIncrease(income_statement->operating_income[year-1], income_statement->operating_income[year]);
        growth += PercentageIncrease(income_statement->ebitda[year-1], income_statement->ebitda[year]);
        growth += PercentageIncrease(balance_sheet->total_assets[year-1], balance_sheet->total_assets[year]);
        growth += PercentageIncrease(balance_sheet->total_shareholder_equity[year-1], balance_sheet->total_shareholder_equity[year]);
        growth += PercentageIncrease(cash_flow->operating_cash_flow[year-1], cash_flow->operating_cash_flow[year]);
        growth += PercentageIncrease(earnings->eps[year-1], earnings->eps[year]);
    }

    return growth / ((historical_years-1)*valuation_data::kGrowthVariables);
}

/// @brief compute percentage increase of 2 numbers
/// @param start_val float original value
/// @param new_val float new value
/// @return float percent increase
float StockValuation::PercentageIncrease(const float start_val, const float new_val) const{
    return (new_val-start_val) / start_val;
}