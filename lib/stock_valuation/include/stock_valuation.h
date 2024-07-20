#pragma once

#include "stock_data.h"
#include "balance_sheet.h"
#include <string>
#include <vector>

class StockValuation
{
public:
    StockValuation(std::string symbol);
private:
    bool ComputeInvestedCapital();

    StockData stock_data;
    BalanceSheet balance_sheet;
};