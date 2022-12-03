#pragma once

#include <string>
#include "client_interfaces.hpp"
#include "unordered_map"


class RequestStringGenerator{
public:
    RequestStringGenerator();
    std::string makeRequestString(std::unordered_map<std::string, std::string> changes, Client::Header request_header);

};
