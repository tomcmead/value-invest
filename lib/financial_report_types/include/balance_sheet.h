#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>

/// @brief Balance sheet data structure
struct BalanceSheet : public FinancialReport
{
public:
    std::map<int, long> total_assets;
    std::map<int, long> total_current_assets;
    std::map<int, long> cash_and_cash_equivalents_at_carrying_value;
    std::map<int, long> cash_and_short_term_investments;
    std::map<int, long> inventory;
    std::map<int, long> current_net_receivables;
    std::map<int, long> total_non_current_assets;
    std::map<int, long> property_plant_equipment;
    std::map<int, long> accumulated_depreciation_amortization_ppe;
    std::map<int, long> intangible_assets;
    std::map<int, long> intangible_assets_excluding_goodwill;
    std::map<int, long> goodwill;
    std::map<int, long> investments;
    std::map<int, long> long_term_investments;
    std::map<int, long> short_term_investments;
    std::map<int, long> other_current_assets;
    std::map<int, long> other_non_current_assets;
    std::map<int, long> total_liabilities;
    std::map<int, long> total_current_liabilities;
    std::map<int, long> current_accounts_payable;
    std::map<int, long> deferred_revenue;
    std::map<int, long> current_debt;
    std::map<int, long> short_term_debt;
    std::map<int, long> total_non_current_liabilities;
    std::map<int, long> capital_lease_obligations;
    std::map<int, long> long_term_debt;
    std::map<int, long> current_long_term_debt;
    std::map<int, long> long_term_debt_non_current;
    std::map<int, long> short_long_term_debt_total;
    std::map<int, long> other_current_liabilities;
    std::map<int, long> other_non_current_liabilities;
    std::map<int, long> total_shareholder_equity;
    std::map<int, long> treasury_stock;
    std::map<int, long> retained_earnings;
    std::map<int, long> common_stock;
    std::map<int, long> common_stock_shares_outstanding;
    const std::vector<std::map<int, long>*> financials = {
        &total_assets, &total_current_assets, &cash_and_cash_equivalents_at_carrying_value,
        &cash_and_short_term_investments, &inventory, &current_net_receivables,
        &total_non_current_assets, &property_plant_equipment,
        &accumulated_depreciation_amortization_ppe, &intangible_assets,
        &intangible_assets_excluding_goodwill, &goodwill, &investments,
        &long_term_investments, &short_term_investments, &other_current_assets,
        &other_non_current_assets, &total_liabilities, &total_current_liabilities,
        &current_accounts_payable, &deferred_revenue, &current_debt, &short_term_debt,
        &total_non_current_liabilities, &capital_lease_obligations, &long_term_debt,
        &current_long_term_debt, &long_term_debt_non_current, &short_long_term_debt_total,
        &other_current_liabilities, &other_non_current_liabilities,
        &total_shareholder_equity, &treasury_stock, &retained_earnings, &common_stock,
        &common_stock_shares_outstanding};
    const std::vector<std::string> financial_names = {
        "totalAssets", "totalCurrentAssets", "cashAndCashEquivalentsAtCarryingValue",
        "cashAndShortTermInvestments", "inventory", "currentNetReceivables",
        "totalNonCurrentAssets", "propertyPlantEquipment",
        "accumulatedDepreciationAmortizationPPE", "intangibleAssets",
        "intangibleAssetsExcludingGoodwill", "goodwill", "investments",
        "longTermInvestments", "shortTermInvestments", "otherCurrentAssets",
        "otherNonCurrentAssets", "totalLiabilities", "totalCurrentLiabilities",
        "currentAccountsPayable", "deferredRevenue", "currentDebt", "shortTermDebt",
        "totalNonCurrentLiabilities", "capitalLeaseObligations", "longTermDebt",
        "currentLongTermDebt", "longTermDebtNoncurrent", "shortLongTermDebtTotal",
        "otherCurrentLiabilities", "otherNonCurrentLiabilities",
        "totalShareholderEquity", "treasuryStock", "retainedEarnings", "commonStock",
        "commonStockSharesOutstanding"};
};