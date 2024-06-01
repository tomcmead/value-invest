#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>

/// @brief Balance sheet data structure
struct BalanceSheet : public FinancialReport
{
public:
    std::map<int, float> total_assets;
    std::map<int, float> total_current_assets;
    std::map<int, float> cash_and_cash_equivalents_at_carrying_value;
    std::map<int, float> cash_and_short_term_investments;
    std::map<int, float> inventory;
    std::map<int, float> current_net_receivables;
    std::map<int, float> total_non_current_assets;
    std::map<int, float> property_plant_equipment;
    std::map<int, float> accumulated_depreciation_amortization_ppe;
    std::map<int, float> intangible_assets;
    std::map<int, float> intangible_assets_excluding_goodwill;
    std::map<int, float> goodwill;
    std::map<int, float> investments;
    std::map<int, float> long_term_investments;
    std::map<int, float> short_term_investments;
    std::map<int, float> other_current_assets;
    std::map<int, float> other_non_current_assets;
    std::map<int, float> total_liabilities;
    std::map<int, float> total_current_liabilities;
    std::map<int, float> current_accounts_payable;
    std::map<int, float> deferred_revenue;
    std::map<int, float> current_debt;
    std::map<int, float> short_term_debt;
    std::map<int, float> total_non_current_liabilities;
    std::map<int, float> capital_lease_obligations;
    std::map<int, float> long_term_debt;
    std::map<int, float> current_long_term_debt;
    std::map<int, float> long_term_debt_non_current;
    std::map<int, float> short_long_term_debt_total;
    std::map<int, float> other_current_liabilities;
    std::map<int, float> other_non_current_liabilities;
    std::map<int, float> total_shareholder_equity;
    std::map<int, float> treasury_stock;
    std::map<int, float> retained_earnings;
    std::map<int, float> common_stock;
    std::map<int, float> common_stock_shares_outstanding;

    const std::vector<std::pair<std::string, std::map<int, float>*>> financials = {
        std::make_pair("totalAssets", &total_assets),
        std::make_pair("totalCurrentAssets", &total_current_assets),
        std::make_pair("cashAndCashEquivalentsAtCarryingValue", &cash_and_cash_equivalents_at_carrying_value),
        std::make_pair("cashAndShortTermInvestments", &cash_and_short_term_investments),
        std::make_pair("inventory", &inventory),
        std::make_pair("currentNetReceivables", &current_net_receivables),
        std::make_pair("totalNonCurrentAssets", &total_non_current_assets),
        std::make_pair("propertyPlantEquipment", &property_plant_equipment),
        std::make_pair("accumulatedDepreciationAmortizationPPE", &accumulated_depreciation_amortization_ppe),
        std::make_pair("intangibleAssets", &intangible_assets),
        std::make_pair("intangibleAssetsExcludingGoodwill", &intangible_assets_excluding_goodwill),
        std::make_pair("goodwill", &goodwill),
        std::make_pair("investments", &investments),
        std::make_pair("longTermInvestments", &long_term_investments),
        std::make_pair("shortTermInvestments", &short_term_investments),
        std::make_pair("otherCurrentAssets", &other_current_assets),
        std::make_pair("otherNonCurrentAssets", &other_non_current_assets),
        std::make_pair("totalLiabilities", &total_liabilities),
        std::make_pair("totalCurrentLiabilities", &total_current_liabilities),
        std::make_pair("currentAccountsPayable", &current_accounts_payable),
        std::make_pair("deferredRevenue", &deferred_revenue),
        std::make_pair("currentDebt", &current_debt),
        std::make_pair("shortTermDebt", &short_term_debt),
        std::make_pair("totalNonCurrentLiabilities", &total_non_current_liabilities),
        std::make_pair("capitalLeaseObligations", &capital_lease_obligations),
        std::make_pair("longTermDebt", &long_term_debt),
        std::make_pair("currentLongTermDebt", &current_long_term_debt),
        std::make_pair("longTermDebtNoncurrent", &long_term_debt_non_current),
        std::make_pair("shortLongTermDebtTotal", &short_long_term_debt_total),
        std::make_pair("otherCurrentLiabilities", &other_current_liabilities),
        std::make_pair("otherNonCurrentLiabilities", &other_non_current_liabilities),
        std::make_pair("totalShareholderEquity", &total_shareholder_equity),
        std::make_pair("treasuryStock", &treasury_stock),
        std::make_pair("retainedEarnings", &retained_earnings),
        std::make_pair("commonStock", &common_stock),
        std::make_pair("commonStockSharesOutstanding", &common_stock_shares_outstanding)};
};