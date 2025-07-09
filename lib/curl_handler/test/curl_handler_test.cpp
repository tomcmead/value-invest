#include "gtest/gtest.h"
#include "curl_handler.h"

namespace http_codes
{
    const std::string kApi_url = "https://mock.httpstatus.io/";
    const int kOk_response = 200;
    const int kUnathorized = 401;
    const int kBad_gateway = 502;
}

TEST(CurlHandler, GetResponsePerformHttpGet_Ok_Return200) {
    std::string response= "";
    const std::string http_ok_url = http_codes::kApi_url + std::to_string(http_codes::kOk_response);
    CurlHandler* curl_handle = CurlHandler::GetInstance();

    long http_code = curl_handle->PerformHttpGet(http_ok_url, response);

    EXPECT_EQ("200 OK", response);
    EXPECT_EQ(http_code, 200);
}

TEST(CurlHandler, GetResponsePerformHttpGet_Unauthorized_Return401) {
    std::string response= "";
    const std::string http_unauthorized_url = http_codes::kApi_url + std::to_string(http_codes::kUnathorized);
    CurlHandler* curl_handle = CurlHandler::GetInstance();

    long http_code = curl_handle->PerformHttpGet(http_unauthorized_url, response);

    EXPECT_EQ("401 Unauthorized", response);
    EXPECT_EQ(http_code, 401);
}

TEST(CurlHandler, GetResponsePerformHttpGet_BadGateway_Return502) {
    std::string response= "";
    const std::string http_bad_gateway_url = http_codes::kApi_url + std::to_string(http_codes::kBad_gateway);
    CurlHandler* curl_handle = CurlHandler::GetInstance();

    long http_code = curl_handle->PerformHttpGet(http_bad_gateway_url, response);

    EXPECT_EQ("502 Bad Gateway", response);
    EXPECT_EQ(http_code, 502);
}