#include <spdlog/spdlog.h>
#include "stock_valuation.h"
#include "stock_data.h"
#include "balance_sheet.h"

#include <string>
#include <vector>
#include <map>

StockValuation::StockValuation(std::string symbol)
{
    spdlog::info("StockValuation::StockValuation");

    stock_data.GetFinancialData<BalanceSheet>(symbol, kBalanceSheet, balance_sheet);
    ComputeInvestedCapital();
}

bool StockValuation::ComputeInvestedCapital()
{
    spdlog::info("StockValuation::ComputeInvestedCapital");

    if(balance_sheet.valid == false)
    {
        return 1;
    }

    for(auto content : balance_sheet.total_assets)
    {
        float operatingCurrentAssets =
            balance_sheet.cash_and_cash_equivalents_at_carrying_value[content.first]
            + balance_sheet.current_net_receivables[content.first]
            + balance_sheet.inventory[content.first]
            + balance_sheet.other_current_assets[content.first];

        float operatingCurrentLiabilities =
            balance_sheet.current_accounts_payable[content.first]
            + balance_sheet.deferred_revenue[content.first];

        float investedCapitalEquity =
            operatingCurrentAssets - operatingCurrentLiabilities
            + balance_sheet.property_plant_equipment[content.first]
            + balance_sheet.capital_lease_obligations[content.first]
            + balance_sheet.other_current_assets[content.first]
            + balance_sheet.goodwill[content.first];

        spdlog::info("{} {}", content.first, investedCapitalEquity);
    }

    return 0;
}