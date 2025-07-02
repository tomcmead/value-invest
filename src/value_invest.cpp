#include "stock_valuation.h"
#include <string>

int main(int argc, char* argv[]){
	StockValuation stock_valuation;
	
    float share_beta = 1;

    for (int i=0; i<argc-1; i++){
        std::string stock_ticker = static_cast<std::string>(argv[i+1]);
		stock_valuation.DiscountedCashFlow(stock_ticker, share_beta);
    }
}