#pragma once

#include <exception>
#include <string>

class DnD_Exception : public std::exception {
 private:
    std::string msg_;

 public:
    DnD_Exception(const char* msg) : msg_(msg) {}

    const char* what() const noexcept override {
        return msg_.c_str();
    }
};
