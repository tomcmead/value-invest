#include "gtest/gtest.h"
#include "curl_handler.h"

TEST(CurlHandler, GetResponsePerformHttpGet_Ok_Return200) {
    std::string response= "";
    CurlHandler* curl_handle = CurlHandler::GetInstance();
    curl_handle->PerformHttpGet("httpstat.us/200", response);
    EXPECT_EQ("200 OK", response);
}

TEST(CurlHandler, GetResponsePerformHttpGet_Unauthorized_Return401) {
    std::string response= "";
    CurlHandler* curl_handle = CurlHandler::GetInstance();
    curl_handle->PerformHttpGet("httpstat.us/401", response);
    EXPECT_EQ("401 Unauthorized", response);
}

TEST(CurlHandler, GetResponsePerformHttpGet_BadGateway_Return502) {
    std::string response= "";
    CurlHandler* curl_handle = CurlHandler::GetInstance();
    curl_handle->PerformHttpGet("httpstat.us/502", response);
    EXPECT_EQ("502 Bad Gateway", response);
}