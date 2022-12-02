#pragma once

#include <string>

namespace DnD {
class ErrorStatus {
 private:
    std::string msg_;
    bool ok_;

    ErrorStatus(bool ok, std::string_view msg) :
        msg_(msg), ok_(ok) {}

 public:
    ErrorStatus() : ErrorStatus(false, "") {}

    bool ok() const {
        return ok_;
    }

    std::string_view msg() const {
        return msg_;
    }

    static ErrorStatus Ok(std::string_view msg = "") {
        return ErrorStatus(true, msg);
    }

    static ErrorStatus Fail(std::string_view msg = "") {
        return ErrorStatus(false, msg);
    }
};
}  // namespace DnD
