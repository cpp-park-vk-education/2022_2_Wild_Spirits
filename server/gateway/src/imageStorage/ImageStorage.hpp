#pragma once

#include <string>

#include <Image.hpp>

class ImageStorage {
public:
    Image getImage(std::string);
    std::string saveImage(Image);
};
