#pragma once

/// @brief Enumerate list of fundamental financial data types
enum FundamentalFinancialType
{
    kIncomeStatement
};

/// @brief Financial data base structure
struct FinancialData
{
public:
    virtual ~FinancialData() = default;
    bool valid;
};