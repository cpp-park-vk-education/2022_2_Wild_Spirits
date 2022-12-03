#pragma once

#include <unordered_map>
#include <string>

typedef std::string string;

class ChangeCollector{
private:
    std::unordered_map<std::string, std::string> changed_fields;
public:
    ChangeCollector();
    void add_change(string description, string new_value);
    std::unordered_map<string, string> flush();
};