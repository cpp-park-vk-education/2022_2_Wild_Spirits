#pragma once

#include <string>
#include "unordered_map"


class RequestStringGenerator{
public:
    RequestStringGenerator();
    std::string makeRequestString(std::unordered_map<std::string, std::string> changes, std::string request_header);
    std::string makeRequestString(std::string change, std::string header);
};
