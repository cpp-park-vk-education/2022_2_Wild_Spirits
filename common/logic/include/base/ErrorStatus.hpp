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
    XX(6, INVALID_TARGET_NUM) \
    XX(7, ALREADY_EXISTS) \
    XX(8, NO_SUCH_ITEM) \
    XX(9, MAXIMUM_DMG_TYPES_EXCEEDED)\
    XX(10, NO_ACTOR_SET) \
    XX(11, SKILL_ON_COOLDOWN)


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
}  // namespace DnD
