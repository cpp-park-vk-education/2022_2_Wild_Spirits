#pragma once

#include <cstddef>

namespace DnD {
    class Identifiable {
        virtual size_t id() const = 0;
    };
}  // namespace DnD
