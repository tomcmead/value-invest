#pragma once

#include "financial_report_types.h"
#include <map>
#include <vector>
#include <string>

/// @brief Cash flow data structure
struct CashFlow : public FinancialReport
{
public:
    std::map<int, float> operating_cash_flow;
    std::map<int, float> payments_for_operating_activities;
    std::map<int, float> proceeds_from_operating_activities;
    std::map<int, float> change_in_operating_liabilities;
    std::map<int, float> change_in_operating_assets;
    std::map<int, float> depreciation_depletion_and_amortization;
    std::map<int, float> capital_expenditures;
    std::map<int, float> change_in_receivables;
    std::map<int, float> change_in_inventory;
    std::map<int, float> profit_loss;
    std::map<int, float> cash_flow_from_investment;
    std::map<int, float> cash_flow_from_financing;
    std::map<int, float> proceeds_from_repayments_of_short_term_debt;
    std::map<int, float> payments_for_repurchase_of_common_stock;
    std::map<int, float> payments_for_repurchase_of_equity;
    std::map<int, float> payments_for_repurchase_of_preferred_stock;
    std::map<int, float> dividend_payout;
    std::map<int, float> dividend_payout_common_stock;
    std::map<int, float> dividend_payout_preferred_stock;
    std::map<int, float> proceeds_from_issuance_of_common_stock;
    std::map<int, float> proceeds_from_issuance_of_long_term_debt_and_capital_securities_net;
    std::map<int, float> proceeds_from_issuance_of_preferred_stock;
    std::map<int, float> proceeds_from_repurchase_of_equity;
    std::map<int, float> proceeds_from_sale_of_treasury_stock;
    std::map<int, float> change_in_cash_and_cash_equivalents;
    std::map<int, float> change_in_exchange_rate;
    std::map<int, float> net_income;

    const std::vector<std::pair<std::string, std::map<int, float>*>> financials = {
        std::make_pair("operatingCashflow", &operating_cash_flow),
        std::make_pair("paymentsForOperatingActivities", &payments_for_operating_activities),
        std::make_pair("proceedsFromOperatingActivities", &proceeds_from_operating_activities),
        std::make_pair("changeInOperatingLiabilities", &change_in_operating_liabilities),
        std::make_pair("changeInOperatingAssets", &change_in_operating_assets),
        std::make_pair("depreciationDepletionAndAmortization", &depreciation_depletion_and_amortization),
        std::make_pair("capitalExpenditures", &capital_expenditures),
        std::make_pair("changeInReceivables", &change_in_receivables),
        std::make_pair("changeInInventory", &change_in_inventory),
        std::make_pair("profitLoss", &profit_loss),
        std::make_pair("cashflowFromInvestment", &cash_flow_from_investment),
        std::make_pair("cashflowFromFinancing", &cash_flow_from_financing),
        std::make_pair("proceedsFromRepaymentsOfShortTermDebt", &proceeds_from_repayments_of_short_term_debt),
        std::make_pair("paymentsForRepurchaseOfCommonStock", &payments_for_repurchase_of_common_stock),
        std::make_pair("paymentsForRepurchaseOfEquity", &payments_for_repurchase_of_equity),
        std::make_pair("paymentsForRepurchaseOfPreferredStock", &payments_for_repurchase_of_preferred_stock),
        std::make_pair("dividendPayout", &dividend_payout),
        std::make_pair("dividendPayoutCommonStock", &dividend_payout_common_stock),
        std::make_pair("dividendPayoutPreferredStock", &dividend_payout_preferred_stock),
        std::make_pair("proceedsFromIssuanceOfCommonStock", &proceeds_from_issuance_of_common_stock),
        std::make_pair("proceedsFromIssuanceOfLongTermDebtAndCapitalSecuritiesNet", &proceeds_from_issuance_of_long_term_debt_and_capital_securities_net),
        std::make_pair("proceedsFromIssuanceOfPreferredStock", &proceeds_from_issuance_of_preferred_stock),
        std::make_pair("proceedsFromRepurchaseOfEquity", &proceeds_from_repurchase_of_equity),
        std::make_pair("proceedsFromSaleOfTreasuryStock", &proceeds_from_sale_of_treasury_stock),
        std::make_pair("changeInCashAndCashEquivalents", &change_in_cash_and_cash_equivalents),
        std::make_pair("changeInExchangeRate", &change_in_exchange_rate),
        std::make_pair("netIncome", &net_income)};
};