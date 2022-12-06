#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>

#include "ErrorStatus.hpp"

namespace DnD {
class StatBased {
 public:
    using Stats = std::unordered_map<std::string, int8_t>;

 private:
    Stats stats_;

    static constexpr int8_t kDefaultStat = 10;
 
 public:
    StatBased() : stats_() {}
    StatBased(const Stats& stats) : stats_(stats) {}

    const Stats& stats() const {
        return stats_;
    }

    int8_t getStat(const std::string& stat) const {
        auto it = stats_.find(stat);
        if (it == stats_.end()) {
            return kDefaultStat;
        }
        return it->second;
    }

    int8_t statBonus(const std::string& stat) const {
        int8_t value = getStat(stat);
        return std::floor((value - 10) / 2.0);
    }

    void setStat(const std::string& stat, int8_t value) {
        stats_[stat] = value;
    }

    void modifyStat(const std::string& stat, int8_t value) {
        int8_t init_value = getStat(stat);
        stats_[stat] = init_value + value;
    }
};
}  // namespace DnD
