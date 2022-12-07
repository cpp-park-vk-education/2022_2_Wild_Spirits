#pragma once

#include <string>

namespace DnD {

#define ERROR_CODES \
    XX(0, OK) \
    XX(-1, UNKNOWN_ERROR) \
    XX(1, INVALID_ARGUMENT) \
    XX(2, OUT_OF_RANGE) \
    XX(3, NO_ACTION_POINTS) \
    XX(4, NO_SPELL_POINTS) \
    XX(5, INVALID_CAST_RANGE) \
    XX(6, NOT_ENOUGH_TARGETS) \
    XX(7, ALREADY_EXISTS) \
    XX(8, NO_SUCH_ITEM) \
    XX(9, MAXIMUM_DMG_TYPES_EXCEEDED)


#define XX(error_code, error_message) \
    error_message = error_code,

enum class ErrorStatus {
    ERROR_CODES
};

#undef XX

#define XX(error_code, error_message) \
    case ErrorStatus::error_message: return #error_message;

inline std::string getErrorMessage(ErrorStatus status) {
    switch(status) {
        ERROR_CODES
        default: return "UNKNOWN";
    }
}

inline std::ostream& operator<<(std::ostream& out, ErrorStatus status) {
    return out << getErrorMessage(status);
}

#undef XX
#undef ERROR_CODES

// class ErrorStatus {
//  private:
//     std::string msg_;
//     bool ok_;

//     ErrorStatus(bool ok, std::string_view msg) :
//         msg_(msg), ok_(ok) {}

//  public:
//     ErrorStatus() : ErrorStatus(false, "") {}

//     bool ok() const {
//         return ok_;
//     }

//     std::string_view msg() const {
//         return msg_;
//     }

//     static ErrorStatus Ok(std::string_view msg = "") {
//         return ErrorStatus(true, msg);
//     }

//     static ErrorStatus Fail(std::string_view msg = "") {
//         return ErrorStatus(false, msg);
//     }

//     static ErrorStatus IdOutOfRange() {
//         return Fail("Id out of range");
//     }
// };
}  // namespace DnD
