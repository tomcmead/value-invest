#include "stock_valuation.h"
#include <string>

int main(int argc, char* argv[]){
    StockValuation stock_valuation;

    // Compute valuation for all stock symbols passed by command line arguments
    for (int i=0; i<argc-1; i++){
        std::string stock_ticker = static_cast<std::string>(argv[i+1]);
        stock_valuation.DiscountedCashFlow(stock_ticker);
    }
}