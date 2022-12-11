#pragma once

#include <string>
#include <vector>

#include <boost/beast/core/detail/base64.hpp>

namespace beast = boost::beast;

class Base64Encoder {
public:
    static std::string encode (const std::string&);
    static std::string decode (const std::string&);
};
