#pragma once

#include <unordered_map>
#include <string>

#include "ErrorStatus.hpp"

namespace DnD {
class StatBased {
 public:
    using Stats = std::unordered_map<std::string, int>;

 private:
    Stats stats_;
 
 public:
    StatBased() : stats_() {}
    StatBased(const Stats& stats) : stats_(stats) {}

    const Stats& stats() const {
        return stats_;
    }

    int getStat(const std::string& stat) const {
        auto it = stats_.find(stat);

        if (it == stats_.end()) {
            return -1;
        }

        return it->second;
    }

    int statBonus(std::string_view) const {
        return 0;
    }

    void setStat(const std::string& stat, int value) {
        stats_[stat] = value;
    }

    ErrorStatus modifyStat(const std::string& stat, int value) {
        if (getStat(stat) == -1) {
            return ErrorStatus::Fail();
        }

        stats_[stat] += value;
        return ErrorStatus::Ok();
    }
};
}  // namespace DnD
