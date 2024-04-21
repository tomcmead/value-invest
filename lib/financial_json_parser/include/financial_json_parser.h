#pragma once

#include <rapidjson/document.h>
#include <string>
#include <vector>

struct FinancialDataType{};

/// @brief Fundamental finacial abstract class
/// converts json string into FinanicalType struct
class FinancialJsonParser
{
public:
    FinancialJsonParser(std::string fundamental_json);
    ~FinancialJsonParser();
    virtual std::vector<int> GetFinancial(FinancialDataType financial_data_type) = 0;
protected:
    rapidjson::Document* json_document;
};