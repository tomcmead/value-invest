#pragma once

namespace json_mocks{
    const std::string kEmpty = "";
    const std::string kValidSharePrice = "{ \
        \"Global Quote\": { \
            \"01. symbol\": \"IBM\",\
            \"02. open\": \"293.1000\",\
            \"03. high\": \"295.6100\",\
            \"04. low\": \"289.4900\",\
            \"05. price\": \"290.4200\",\
            \"06. volume\": \"2925329\",\
            \"07. latest trading day\": \"2025-07-08\",\
            \"08. previous close\": \"292.4700\",\
            \"09. change\": \"-2.0500\",\
            \"10. change percent\": \"-0.7009%\"\
        }}";
    const std::string kInvalidSharePrice = "{test: 2.13}";

        // const std::string kValidIncomeStatement = "test";
    // const std::string kInvalidIncomeStatement = "test";
    // const std::string kValidBalanceSheet = "test";
    // const std::string kInvalidBalanceSheet = "test";
    // const std::string kValidCashFlow = "test";
    // const std::string kInvalidCashFlow = "test";
    // const std::string kValidEarnings = "test";
    // const std::string kInvalidEarnings = "test";
    // const std::string kValidStockOverview = "test";
    // const std::string kInvalidStockOverview = "test";
    // const std::string kValidTreasury = "test";
    // const std::string kInvalidTreasury = "test";
}