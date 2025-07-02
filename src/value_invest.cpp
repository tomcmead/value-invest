#include "stock_valuation.h"
#include <string>

int main(int argc, char* argv[]){
	StockValuation stock_valuation;
	
    int forecast_years = 5;
    float share_beta = 1;
    float growth_percent = 5;

    for (int i=0; i<argc-1; i++){
        std::string stock_ticker = static_cast<std::string>(argv[i+1]);
		stock_valuation.DiscountedCashFlow(stock_ticker, forecast_years,
			share_beta, growth_percent);
    }
}