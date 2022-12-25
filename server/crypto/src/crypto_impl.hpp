#pragma once

#include <arpa/inet.h>

#include <cstddef>
#include <cstdint>

#include <array>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace Crypto {
std::vector<unsigned char> format_input(const std::string& input);

template <size_t hash_num_, size_t chunk_size_>
class SHA {
 protected:
    std::vector<unsigned char> input_;
    std::array<uint32_t, chunk_size_> work_array_;
    std::array<uint32_t, hash_num_> hashes_;

    SHA(const std::string& input, const std::array<uint32_t, hash_num_>& hashes) :
        input_(format_input(input)),
        work_array_(),
        hashes_(hashes) {}

    virtual void preprocess_chunk() = 0;
    virtual std::array<uint32_t, hash_num_> compress() = 0;

    void make_chunk(size_t start) {
        // We will process our input by 32 bit pieces
        auto view = reinterpret_cast<const uint32_t*>(input_.data() + start);
        std::copy(view, view + 16, work_array_.data());

        // Reverse byte order. I pray that this is somewhat portable
        // htonl is Unix-only
        for (size_t i = 0; i < 16; ++i) {
            work_array_[i] = htonl(work_array_[i]);
        }
    }

    inline void update_hash(const std::array<uint32_t, hash_num_>& to_add) {
        std::transform(to_add.cbegin(), to_add.cend(),
                        hashes_.cbegin(), hashes_.begin(),
                        std::plus{});
    }

 public:
    std::array<uint32_t, hash_num_> compute() {
        for (size_t i = 0; i < input_.size() / 64; ++i) {
            make_chunk(i * 64);
            preprocess_chunk();
            update_hash(compress());
        }
        return hashes_;
    }
};

class SHA1_Impl : public SHA<5, 80> {
 private:
    using sha1_op = std::function<uint32_t(uint32_t, uint32_t, uint32_t)>;

    static const std::array<uint32_t, 5> init_hashes_;
    static const std::pair<uint32_t, sha1_op> magic_constants_[];

    void preprocess_chunk() override;
    std::array<uint32_t, 5> compress() override;

 public:
    explicit SHA1_Impl(const std::string& input);
};

class SHA256_Impl : public SHA<8, 64> {
 private:
    static const std::array<uint32_t, 8> init_hashes_;
    static const uint32_t magic_constants_[];

    void preprocess_chunk() override;
    std::array<uint32_t, 8> compress() override;

 public:
    explicit SHA256_Impl(const std::string& input);
};
}  // namespace Crypto
