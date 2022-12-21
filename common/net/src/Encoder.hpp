#pragma once

#include <string>
#include <vector>

class Base64Encoder {
public:
    static std::string encode (const std::string&);
    static std::string decode (const std::string&);
};
