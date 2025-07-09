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
    const std::string kInvalidSharePrice = "{Global Quote{\": {05. price\": \"INVALID\"}";
    const std::string kValidStockOverview = "{\
        \"Symbol\": \"IBM\",\
        \"AssetType\": \"Common Stock\",\
        \"Name\": \"International Business Machines\",\
        \"Description\": \"International\",\
        \"CIK\": \"51143\",\
        \"Exchange\": \"NYSE\",\
        \"Currency\": \"USD\",\
        \"Country\": \"USA\",\
        \"Sector\": \"TECHNOLOGY\",\
        \"Industry\": \"COMPUTER & OFFICE EQUIPMENT\",\
        \"Address\": \"1 NEW ORCHARD ROAD, ARMONK, NY, US\",\
        \"OfficialSite\": \"https://www.ibm.com\",\
        \"FiscalYearEnd\": \"December\",\
        \"LatestQuarter\": \"2025-03-31\",\
        \"MarketCapitalization\": \"271820734000\",\
        \"EBITDA\": \"13950000000\",\
        \"PERatio\": \"49.99\",\
        \"PEGRatio\": \"2.168\",\
        \"BookValue\": \"28.92\",\
        \"DividendPerShare\": \"6.68\",\
        \"DividendYield\": \"0.0228\",\
        \"EPS\": \"5.85\",\
        \"RevenuePerShareTTM\": \"67.97\",\
        \"ProfitMargin\": \"0.0871\",\
        \"OperatingMarginTTM\": \"0.124\",\
        \"ReturnOnAssetsTTM\": \"0.0447\",\
        \"ReturnOnEquityTTM\": \"0.218\",\
        \"RevenueTTM\": \"62832001000\",\
        \"GrossProfitTTM\": \"35840000000\",\
        \"DilutedEPSTTM\": \"5.85\",\
        \"QuarterlyEarningsGrowthYOY\": \"-0.349\",\
        \"QuarterlyRevenueGrowthYOY\": \"0.005\",\
        \"AnalystTargetPrice\": \"258.02\",\
        \"AnalystRatingStrongBuy\": \"2\",\
        \"AnalystRatingBuy\": \"8\",\
        \"AnalystRatingHold\": \"9\",\
        \"AnalystRatingSell\": \"2\",\
        \"AnalystRatingStrongSell\": \"1\",\
        \"TrailingPE\": \"49.99\",\
        \"ForwardPE\": \"26.67\",\
        \"PriceToSalesRatioTTM\": \"4.326\",\
        \"PriceToBookRatio\": \"10.11\",\
        \"EVToRevenue\": \"5.11\",\
        \"EVToEBITDA\": \"26.05\",\
        \"Beta\": \"0.652\",\
        \"52WeekHigh\": \"296.16\",\
        \"52WeekLow\": \"169.32\",\
        \"50DayMovingAverage\": \"266.77\",\
        \"200DayMovingAverage\": \"241.28\",\
        \"SharesOutstanding\": \"929397000\",\
        \"SharesFloat\": \"927361000\",\
        \"PercentInsiders\": \"0.119\",\
        \"PercentInstitutions\": \"65.274\",\
        \"DividendDate\": \"2025-06-10\",\
        \"ExDividendDate\": \"2025-05-09\"\
    }";
    const std::string kInvalidStockOverview = "{\"test\": \"INVALID\"}";
    const std::string kValidTreasuryYield = "{\
        \"name\": \"10-Year Treasury Constant Maturity Rate\",\
        \"interval\": \"monthly\",\
        \"unit\": \"percent\",\
        \"data\": [\
            {\
                \"date\": \"2025-06-01\",\
                \"value\": \"4.38\"\
            },\
            {\
                \"date\": \"2025-05-01\",\
                \"value\": \"4.42\"\
            },\
            {\
                \"date\": \"2025-04-01\",\
                \"value\": \"4.28\"\
    }]}";
    const std::string kInvalidTreasuryYield = "{\"data\": [{\
        \"date\": \"2025-06-01\",\
        \"value\": \"INVALID\"\
    }]}";
}