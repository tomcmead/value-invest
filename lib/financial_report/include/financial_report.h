#pragma once

/// @brief Enumerate list of fundamental financial data types
enum FinancialReportType
{
    kIncomeStatement
};

/// @brief Financial data base structure
struct FinancialReport
{
public:
    virtual ~FinancialReport() = default;
    bool valid;
};