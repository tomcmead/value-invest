#include "stock_valuation.h"

int main()
{
    std::string stock_ticker = "AAPL";
    float share_price = 200;
    int forecast_years = 5;
    float share_beta = 1;
    float growth_percent = 5;

    StockValuation stock_valuation;
    stock_valuation.DiscountedCashFlow(stock_ticker, share_price, forecast_years,
        share_beta, growth_percent);
}