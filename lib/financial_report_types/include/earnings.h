#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>
#include <utility>

/// @brief Earnings data structure
struct Earnings : public FinancialReport
{
public:
    std::map<int, float> eps;
    const std::vector<std::pair<std::string, std::map<int, float>*>> financials = {
        std::make_pair("reportedEPS", &eps)};
};