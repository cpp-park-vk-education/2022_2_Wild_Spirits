#include <Encoder.hpp>

#include <iostream>

std::string Base64Encoder::encode(const std::string& in) {
    std::string out;

    const auto symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    unsigned int val = 0;
    int valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(symbols[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(symbols[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string Base64Encoder::decode(const std::string& in) {
    std::string out;

    const auto symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[symbols[i]] = i;

    unsigned int val = 0;
    int valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6u) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<char>((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    return out;
}
