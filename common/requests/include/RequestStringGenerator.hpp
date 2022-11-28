#pragma once


#include "client_interfaces.hpp"
#include "unordered_map"


class RequestStringGenerator{
public:

    std::string makeRequestString(std::unordered_map<std::string, std::string>, Client::Header);

};
