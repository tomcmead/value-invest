#pragma once

/// @brief Enumerate list of fundamental financial data types
enum FinancialReportType
{
    kIncomeStatement,
    kBalanceSheet,
    kCashFlow,
    kEarnings,
	kSharePrice,
	kBeta
};

/// @brief Financial report base structure
struct FinancialReport
{
public:
    virtual ~FinancialReport() = default;
    bool valid;
};