#include "StatBased.hpp"

namespace DnD {
    StatBased::Stats StatBased::defaultStats() {
        return Stats{
            {"dex", 10},
            {"str", 10},
            {"int", 10},
            {"wis", 10},
            {"cha", 10},
            {"cns", 10}
        };
    }
} // namespace DnD
