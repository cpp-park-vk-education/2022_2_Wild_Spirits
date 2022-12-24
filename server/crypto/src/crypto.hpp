#pragma once

#include <array>
#include <string>
#include <sstream>

namespace Crypto {
    template <size_t size>
    inline std::string hashes_to_str(const std::array<uint32_t, size>& hashes) {
        std::stringstream out;
        out << std::hex;
        for (auto elem : hashes) {
            out << elem;
        }
        return out.str();
    }

    std::array<uint32_t, 8> SHA256(const std::string& input);
    std::array<uint32_t, 5> SHA1(const std::string& input);

    inline std::string SHA256_STR(const std::string &input) {
        return hashes_to_str(SHA256(input));
    }
}  // namespace Crypto
