#pragma once

#include <exception>
#include <string>

namespace DnD {
class Exception : public std::exception {
 private:
    std::string msg_;

 public:
    Exception(const char* msg) : msg_(msg) {}

    const char* what() const noexcept override {
        return msg_.c_str();
    }
};

class OutOfRange : public Exception {
 public:
    OutOfRange() :
        Exception("Index out of range") {}
};
}  // namespace DnD
