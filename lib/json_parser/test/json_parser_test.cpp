#include "gtest/gtest.h"
#include "json_parser.h"
#include "json_mocks.h"
#include "error_codes.h"

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

    const bool result = json_parser.ParseMiscData(json_mocks::kValidSharePrice, misc_type::SharePrice, share_price);

    EXPECT_EQ(result, error_codes::Success);
    EXPECT_EQ(share_price, 290.42);
}

TEST(JsonParser, ParseMiscData_InvalidSharePrice_ReturnFalse) {
    JsonParser json_parser;
    float misc_data = 0;

    const bool result = json_parser.ParseMiscData(json_mocks::kInvalidSharePrice, misc_type::SharePrice, misc_data);

    EXPECT_EQ(result, error_codes::Fail);
    EXPECT_EQ(misc_data, 0);
}