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
    
    static int calculateStatBonus(unsigned int value) {
        return std::floor((value - 10) / 2.0);
    }
 
 public:
    StatBased() : stats_() {}
    StatBased(const Stats& stats) : stats_(stats) {}

    static Stats defaultStats();

    const Stats& stats() const {
        return stats_;
    }

    int8_t stat(const std::string& stat) const {
        auto it = stats_.find(stat);
        if (it == stats_.end()) {
            return kDefaultStat;
        }
        return it->second;
    }

    bool hasStat(const std::string& stat_name) const {
        return stats_.find(stat_name) != stats_.end();
    }

    int8_t statBonus(const std::string& stat_name) const {
        return calculateStatBonus(stat(stat_name));
    }

    void setStat(const std::string& stat_name, int8_t value) {
        stats_[stat_name] = value;
    }

    void modifyStat(const std::string& stat_name, int8_t value) {
        int8_t init_value = stat(stat_name);
        stats_[stat_name] = init_value + value;
    }

    friend class CharacterInstance;
};
}  // namespace DnD
