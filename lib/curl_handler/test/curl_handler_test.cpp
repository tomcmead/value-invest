#include "gtest/gtest.h"
#include "curl_handler.h"

TEST(CurlHandler, GetResponsePerformHttpGet_200_ReturnOkResponse) {
    std::string response= "";
    CurlHandler* curl_handle = CurlHandler::GetInstance();
    curl_handle->PerformHttpGet("httpstat.us/200", response);
    EXPECT_EQ("200 OK", response);
}