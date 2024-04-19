#pragma once

#include <rapidjson/document.h>
#include <string>
#include <vector>

struct FinancialType{};

/// @brief Fundamental finacial abstract class
/// converts json string into FinanicalType struct
class FinancialJson
{
public:
    FinancialJson(std::string fundamental_json);
    ~FinancialJson();
    virtual std::vector<int> GetFinancial(FinancialType financial_data_type) = 0;
protected:
    rapidjson::Document* json_document;
};