#include "gtest/gtest.h"
#include "json_parser.h"
#include "json_mocks.h"
#include "error_codes.h"
#include "stock_overview.h"

TEST(JsonParser, ParseMiscData_InvalidEmptyJson_ReturnFalse) {
    JsonParser json_parser;
    float misc_data = 0;

    const bool result = json_parser.ParseMiscData(json_mocks::kEmpty, misc_type::SharePrice, misc_data);

    EXPECT_EQ(result, error_codes::Fail);
    EXPECT_EQ(misc_data, 0);
}

TEST(JsonParser, ParseMiscData_ValidSharePrice_ReturnTrue) {
    JsonParser json_parser;
    float share_price = 0;
    const float kShare_price_result = 290.42;

    const bool result = json_parser.ParseMiscData(json_mocks::kValidSharePrice, misc_type::SharePrice, share_price);

    EXPECT_EQ(result, error_codes::Success);
    EXPECT_EQ(share_price, kShare_price_result);
}

TEST(JsonParser, ParseMiscData_InvalidSharePrice_ReturnFalse) {
    JsonParser json_parser;
    float misc_data = 0;

    const bool result = json_parser.ParseMiscData(json_mocks::kInvalidSharePrice, misc_type::SharePrice, misc_data);

    EXPECT_EQ(result, error_codes::Fail);
    EXPECT_EQ(misc_data, 0);
}


TEST(JsonParser, ParseStockOverview_InvalidEmptyJson_ReturnNull) {
    JsonParser json_parser;
    std::unique_ptr<StockOverview> stock_overview = std::make_unique<StockOverview>();

    stock_overview = json_parser.ParseStockOverview(json_mocks::kEmpty);

    EXPECT_EQ(stock_overview, nullptr);
}

TEST(JsonParser, ParseStockOverview_ValidOverview_ReturnValid) {
    JsonParser json_parser;
    std::unique_ptr<StockOverview> stock_overview = std::make_unique<StockOverview>();

    stock_overview = json_parser.ParseStockOverview(json_mocks::kValidStockOverview);

    EXPECT_EQ(stock_overview->market_capitalization, 271820734000);
    EXPECT_EQ(stock_overview->ebitda, 13950000000);
    EXPECT_EQ(stock_overview->pe_ratio, 49.99f);
    EXPECT_EQ(stock_overview->peg_ratio, 2.168f);
    EXPECT_EQ(stock_overview->book_value, 28.92f);
    EXPECT_EQ(stock_overview->eps, 5.85f);
    EXPECT_EQ(stock_overview->price_to_book_ratio, 10.11f);
    EXPECT_EQ(stock_overview->beta, 0.652f);
    EXPECT_EQ(stock_overview->shares_outstanding, 929397000);
    EXPECT_EQ(stock_overview->percent_insiders, 0.119f);
    EXPECT_EQ(stock_overview->percent_institutions, 65.274f);
    EXPECT_EQ(stock_overview->valid, true);
}

TEST(JsonParser, ParseStockOverview_InvalidOverview_ReturnNull) {
    JsonParser json_parser;
    std::unique_ptr<StockOverview> stock_overview = std::make_unique<StockOverview>();

    stock_overview = json_parser.ParseStockOverview(json_mocks::kInvalidStockOverview);

    EXPECT_EQ(stock_overview, nullptr);
}