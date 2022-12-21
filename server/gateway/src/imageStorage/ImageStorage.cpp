#include <ImageStorage.hpp>

#include <iostream>

ImageStorage::ImageStorage(const fs::path &dir_path): dir_path(dir_path) {
    if (!fs::exists(dir_path)) {
        fs::create_directory(dir_path);
    }
}

ImageStorage::image_ptr_t ImageStorage::getImage(const std::string &hash) {
    const fs::path path = dir_path / fs::path(hash);
    if (fs::exists(path)) {
        return std::make_shared<LazyImage>(path);
    }

    return image_ptr_t();
}

std::string ImageStorage::saveImage(const std::string &data, const std::string &extension) const {
    auto t = std::chrono::system_clock::now().time_since_epoch().count();
    std::string hash = std::to_string(t) + "." + extension;

    fs::path path = dir_path / fs::path(hash);

    std::cout << path.string() << std::endl;

    LazyImage::saveImage(path, data);

    return hash;
}
