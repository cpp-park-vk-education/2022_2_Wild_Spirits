#include "crypto.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <string>
#include <utility>

#include "crypto_impl.hpp"

namespace Crypto {

std::vector<unsigned char> format_input(const std::string& input) {
    std::vector<unsigned char> bytes(input.begin(), input.end());

    // Reserve exact amount of memory we would need
    bytes.reserve(((input.size() - 1) / 64 * 64) + 64);

    // Add 1 one bit and 7 zero bits
    bytes.push_back(128);

    // Fill with zeroes till bitsize is dividable by 512
    while ((bytes.size() + 8) % 64) {
        bytes.push_back(0);
    }

    // Add size of the original input in bits
        // with bytes order reversed
    uint64_t bit_size = input.size() * 8;
    const char* size_as_bytes = reinterpret_cast<const char*>(&bit_size);

    for (ssize_t i = 7; i >= 0; --i) {
        bytes.push_back(size_as_bytes[i]);
    }

    return bytes;
}

std::array<uint32_t, 8> SHA256(const std::string& input) {
    return SHA256_Impl(input).compute();
}

std::array<uint32_t, 5> SHA1(const std::string& input) {
    return SHA1_Impl(input).compute();
}

SHA1_Impl::SHA1_Impl(const std::string& input) :
    SHA(input, init_hashes_) {}

void SHA1_Impl::preprocess_chunk() {
    for (size_t i = 16; i < work_array_.size(); ++i) {
        uint32_t tmp = work_array_[i - 3] ^ work_array_[i - 8] ^
                       work_array_[i - 14] ^ work_array_[i - 16];
        work_array_[i] = std::rotl(tmp, 1);
    }
}

std::array<uint32_t, 5> SHA1_Impl::compress() {
    auto [a, b, c, d, e] = init_hashes_;

    for (size_t i = 0; i < work_array_.size(); ++i) {
        auto [k, func] = magic_constants_[i / 20];
        uint32_t f = func(b, c, d);

        uint32_t tmp = std::rotl(a, 5) + f + e + k + work_array_[i];
        e = d;
        d = c;
        c = std::rotl(b, 30);
        b = a;
        a = tmp;
    }

    return std::array<uint32_t, 5>{a, b, c, d, e};
}

const std::pair<uint32_t, SHA1_Impl::sha1_op> SHA1_Impl::magic_constants_[] = {
    {0x5A827999, [] (auto b, auto c, auto d) {
        return (b & c) | (~b & d);
    }},
    {0x6ED9EBA1, [] (auto b, auto c, auto d) {
        return b ^ c ^ d;
    }},
    {0x8F1BBCDC, [] (auto b, auto c, auto d) {
        return (b & c) | (b & d) | (c & d);
    }},
    {0xCA62C1D6, [] (auto b, auto c, auto d) {
        return b ^ c ^ d;
    }}
};

const std::array<uint32_t, 5> SHA1_Impl::init_hashes_ = {
        0x67452301, 0xEFCDAB89,
        0x98BADCFE, 0x10325476, 0xC3D2E1F0
};

SHA256_Impl::SHA256_Impl(const std::string& input) :
    SHA(input, init_hashes_) {}

const uint32_t SHA256_Impl::magic_constants_[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

const std::array<uint32_t, 8> SHA256_Impl::init_hashes_ = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                                           0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

void SHA256_Impl::preprocess_chunk() {
    std::fill(work_array_.begin() + 16, work_array_.end(), 0);

    for (size_t i = 16; i < 64; ++i) {
        uint32_t s0 = std::rotr(work_array_[i - 15], 7) ^
                      std::rotr(work_array_[i - 15], 18) ^
                        (work_array_[i - 15] >> 3);

        uint32_t s1 = std::rotr(work_array_[i - 2], 17) ^
                      std::rotr(work_array_[i - 2], 19) ^
                        (work_array_[i - 2] >> 10);

        work_array_[i] = work_array_[i - 16] + s0 + work_array_[i - 7]+ s1;
    }
}

std::array<uint32_t, 8> SHA256_Impl::compress() {
    auto [a, b, c, d, e, f, g, h] = init_hashes_;

    for (size_t i = 0; i < 64; ++i) {
        uint32_t S0 = std::rotr(a, 2) ^ std::rotr(a, 13) ^ std::rotr(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;
        uint32_t S1 = std::rotr(e, 6) ^ std::rotr(e, 11) ^ std::rotr(e, 25);
        uint32_t ch = (e & f) ^ ((~e) & g);
        uint32_t temp1 = h + S1 + ch + magic_constants_[i] + work_array_[i];

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    return std::array<uint32_t, 8>{a, b, c, d, e, f, g, h};
}
}  // namespace Crypto
