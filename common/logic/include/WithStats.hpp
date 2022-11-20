#pragma once

#include <unordered_map>
#include <string>

#include "Utils.hpp"

class WithStats {
 public:
    using Stats = std::unordered_map<std::string, int>;

 private:
    Stats stats_;
 
 public:
    WithStats() : stats_() {}
    WithStats(const Stats& stats) : stats_(stats) {}

    int getStat(const std::string& stat) const {
        auto it = stats_.find(stat);

        if (it == stats_.end()) {
            return -1;
        }

        return it->second;
    }

    void setStat(const std::string& stat, int value) {
        stats_[stat] = value;
    }

    ErrorStatus modifyStat(const std::string& stat, int value) {
        if (getStat(stat) == -1) {
            return ErrorStatus::Fail;
        }

        stats_[stat] += value;
        return ErrorStatus::Ok;
    }
};
