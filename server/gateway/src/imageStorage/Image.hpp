#pragma once

#include <string>
#include <iterator>
#include <memory>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

#include <Encoder.hpp>

class Image {
public:
    using image_ptr_t = std::shared_ptr<Image>;

    virtual fs::path getPath() = 0;
    virtual std::string getData() = 0;
    virtual std::string getBase64() = 0;
};

class LazyImage: public Image {
private:
    fs::path path;

public:
    explicit LazyImage (const fs::path &path);

    virtual ~LazyImage() {}

    static image_ptr_t saveImage(const fs::path &path, const std::string &data);

    virtual fs::path getPath() override;
    virtual std::string getData() override;
    virtual std::string getBase64() override;
};
