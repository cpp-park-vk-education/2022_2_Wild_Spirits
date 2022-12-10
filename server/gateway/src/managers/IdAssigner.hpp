#pragma once

#include <queue>

class IdAssigner {
public:
    virtual std::size_t assignId() = 0;
};

class ReuseIdAssigner: public IdAssigner {
private:
    std::queue<std::size_t> deleted_ids;
    std::size_t counter;

public:
    ReuseIdAssigner(): counter(0) {}

    std::size_t countDeletedIds() const {
        return deleted_ids.size();
    }

    std::size_t assignId() override {
        if (deleted_ids.empty()) {
            return counter++;
        }

        std::size_t id = deleted_ids.front();
        deleted_ids.pop();
        return id;
    }

    void releaseId(std::size_t id) {
        deleted_ids.push(id);
    }
};

class UniqueIdAssigner: public IdAssigner {
private:
    std::size_t counter;

public:
    UniqueIdAssigner(): counter(0) {}

    std::size_t assignId() override {
        return counter++;
    }
};