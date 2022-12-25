#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include <Image.hpp>

namespace fs = std::filesystem;

class ImageStorage {
private:
    fs::path dir_path;

public:
    using image_ptr_t = std::shared_ptr<Image>;

    explicit ImageStorage(const fs::path &dir_path);

    image_ptr_t getImage(const std::string &hash);
    std::string saveImage(const std::string &data, const std::string &extension) const;
};
