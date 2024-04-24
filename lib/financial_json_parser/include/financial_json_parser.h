#pragma once

#include <rapidjson/document.h>
#include <string>
#include <vector>

struct FinancialData{};

/// @brief Fundamental finacial abstract class
/// converts json string into FinanicalType struct
class FinancialJsonParser
{
public:
    FinancialJsonParser(std::string fundamental_json);
    ~FinancialJsonParser();
    virtual void GetFinancial(FinancialData& financial_data) = 0;
protected:
    rapidjson::Document json_document;
};