#pragma once

#include <unordered_map>
typedef std::string string;

class ChangeCollector{
private:
    std::unordered_map<std::string, std::string> changed_fields;
public:
    void add_change(string description, string new_value);
    std::unordered_map<string, string> flush();
};