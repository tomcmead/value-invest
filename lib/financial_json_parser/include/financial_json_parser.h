#pragma once

#include <rapidjson/document.h>
#include <string>
#include <vector>

/// @brief Financial data base structure
struct FinancialData{};

/// @brief Fundamental finacial base class
/// 'adapter' design pattern converts json string into FinanicalData struct
class FinancialJsonParser
{
public:
    FinancialJsonParser(std::string fundamental_json);
    ~FinancialJsonParser();
    virtual void GetFinancial(FinancialData& financial_data) = 0;
protected:
    rapidjson::Document json_document;
};