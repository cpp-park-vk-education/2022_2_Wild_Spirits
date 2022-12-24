#pragma once

#include "Activatable.hpp"

namespace DnD {
template <std::derived_from<Activatable> T>
class ActivatableProxy : public ActivatableInterface {
 private:
    bool was_updated_ = false;
    const std::shared_ptr<T> original_;

    void toggleUpdated() {
        was_updated_ = !was_updated_;
    }

 public:
    ActivatableProxy(const std::shared_ptr<T>& original) : original_(original) {}

    const T& original() const {
        return *original_;
    }

    size_t id() const override {
        return original_->id();
    }

    unsigned int activateCost() const override {
        return original_->activateCost();
    }

    const std::string& scalesBy() const override {
        return original_->scalesBy();
    }

    Cast castType() const override {
        return original_->castType();
    }

    bool canMiss() const override {
        return original_->canMiss();
    }

    const std::vector<Action>& actions() const override {
        return original_->actions();
    }

    std::string& info(const std::string& key) override {
        return original_->info(key);
    }

    const Info& info() const override {
        return original_->info();
    }

    const std::string& name() const override {
        return original_->name();
    }

    void setName(std::string_view name) override {
        original_->setName(name);
    }

    size_t getImageId() const override {
        return original_->getImageId();
    }

    void setImage(size_t id) override {
        original_->setImage(id);
    }

    bool wasUpdated() const {
        return was_updated_;
    }
};
} // namespace DnD
