#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>

/// @brief Cash flow data structure
struct CashFlow : public FinancialReport
{
public:
    std::map<int, long> operating_cash_flow;
    std::map<int, long> payments_for_operating_activities;
    std::map<int, long> proceeds_from_operating_activities;
    std::map<int, long> change_in_operating_liabilities;
    std::map<int, long> change_in_operating_assets;
    std::map<int, long> depreciation_depletion_and_amortization;
    std::map<int, long> capital_expenditures;
    std::map<int, long> change_in_receivables;
    std::map<int, long> change_in_inventory;
    std::map<int, long> profit_loss;
    std::map<int, long> cash_flow_from_investment;
    std::map<int, long> cash_flow_from_financing;
    std::map<int, long> proceeds_from_repayments_of_short_term_debt;
    std::map<int, long> payments_for_repurchase_of_common_stock;
    std::map<int, long> payments_for_repurchase_of_equity;
    std::map<int, long> payments_for_repurchase_of_preferred_stock;
    std::map<int, long> dividend_payout;
    std::map<int, long> dividend_payout_common_stock;
    std::map<int, long> dividend_payout_preferred_stock;
    std::map<int, long> proceeds_from_issuance_of_common_stock;
    std::map<int, long> proceeds_from_issuance_of_long_term_debt_and_capital_securities_net;
    std::map<int, long> proceeds_from_issuance_of_preferred_stock;
    std::map<int, long> proceeds_from_repurchase_of_equity;
    std::map<int, long> proceeds_from_sale_of_treasury_stock;
    std::map<int, long> change_in_cash_and_cash_equivalents;
    std::map<int, long> change_in_exchange_rate;
    std::map<int, long> net_income;
    const std::vector<std::map<int, long>*> financials = {
        &operating_cash_flow,
        &payments_for_operating_activities,
        &proceeds_from_operating_activities,
        &change_in_operating_liabilities,
        &change_in_operating_assets,
        &depreciation_depletion_and_amortization,
        &capital_expenditures,
        &change_in_receivables,
        &change_in_inventory,
        &profit_loss,
        &cash_flow_from_investment,
        &cash_flow_from_financing,
        &proceeds_from_repayments_of_short_term_debt,
        &payments_for_repurchase_of_common_stock,
        &payments_for_repurchase_of_equity,
        &payments_for_repurchase_of_preferred_stock,
        &dividend_payout,
        &dividend_payout_common_stock,
        &dividend_payout_preferred_stock,
        &proceeds_from_issuance_of_common_stock,
        &proceeds_from_issuance_of_long_term_debt_and_capital_securities_net,
        &proceeds_from_issuance_of_preferred_stock,
        &proceeds_from_repurchase_of_equity,
        &proceeds_from_sale_of_treasury_stock,
        &change_in_cash_and_cash_equivalents,
        &change_in_exchange_rate,
        &net_income};
    const std::vector<std::string> financial_names = {
        "operatingCashflow",
        "paymentsForOperatingActivities",
        "proceedsFromOperatingActivities",
        "changeInOperatingLiabilities",
        "changeInOperatingAssets",
        "depreciationDepletionAndAmortization",
        "capitalExpenditures",
        "changeInReceivables",
        "changeInInventory",
        "profitLoss",
        "cashflowFromInvestment",
        "cashflowFromFinancing",
        "proceedsFromRepaymentsOfShortTermDebt",
        "paymentsForRepurchaseOfCommonStock",
        "paymentsForRepurchaseOfEquity",
        "paymentsForRepurchaseOfPreferredStock",
        "dividendPayout",
        "dividendPayoutCommonStock",
        "dividendPayoutPreferredStock",
        "proceedsFromIssuanceOfCommonStock",
        "proceedsFromIssuanceOfLongTermDebtAndCapitalSecuritiesNet",
        "proceedsFromIssuanceOfPreferredStock",
        "proceedsFromRepurchaseOfEquity",
        "proceedsFromSaleOfTreasuryStock",
        "changeInCashAndCashEquivalents",
        "changeInExchangeRate",
        "netIncome"};
};