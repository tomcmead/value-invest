#pragma once

#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>

/// @brief Balance sheet data structure
struct StockOverview
{
public:
    float market_capitalization;
    float ebitda;
    float pe_ratio;
    float peg_ratio;
    float book_value;
    float eps;
    float price_to_book_ratio;
    float beta;
    float shares_outstanding;
    float percent_insiders;
    float percent_institutions;
    bool valid;
};