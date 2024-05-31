#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>

/// @brief Earnings data structure
struct Earnings : public FinancialReport
{
public:
    std::map<int, long> eps;
    const std::vector<std::map<int, long>*> financials = {
        &eps};
    const std::vector<std::string> financial_names = {
        "reportedEPS"};
};