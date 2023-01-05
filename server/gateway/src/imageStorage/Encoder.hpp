#pragma once

#include <string>
#include <vector>

class Base64Encoder {
public:
    static std::string encode (std::vector<std::byte>);
    static std::vector<std::byte> decode (std::string);
};