#include <Image.hpp>

LazyImage::LazyImage(const fs::path &path): path(path) {}

fs::path LazyImage::getPath() {
    return path;
}

std::string LazyImage::getData() {
    std::ifstream file;
    file.open(path);

    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string LazyImage::getBase64() {
    return Base64Encoder::encode(getData());
}

LazyImage::image_ptr_t LazyImage::saveImage(const fs::path &path, const std::string &data) {
    std::ofstream file(path);

    std::string file_contents = Base64Encoder::decode(data);

    file << file_contents;
    file.close();

    return std::make_shared<LazyImage>(path);
}
