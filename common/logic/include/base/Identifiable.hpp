#pragma once

#include <cstddef>

namespace DnD {
    class Identifiable {
      public:
        virtual size_t id() const = 0;
    };
}  // namespace DnD
