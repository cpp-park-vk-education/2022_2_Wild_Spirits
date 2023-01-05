#pragma once

#include <string>

struct Image {
    std::string path;
    std::string data;

    std::string getBase64();
};
