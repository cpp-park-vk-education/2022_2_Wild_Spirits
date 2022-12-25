#pragma once

#include <unordered_map>
#include <string>
#include <variant>

#include "ErrorStatus.hpp"
#include "Identifiable.hpp"
#include "DynamiclySettable.hpp"

namespace DnD {
class GameEntityInterface : virtual public Identifiable, virtual public DynamiclySettable {
 protected:
    using Info = std::unordered_map<std::string, std::string>;

 private:
    virtual void toggleUpdated() = 0;

 public:
    virtual std::string& info(const std::string&) = 0;
    virtual const Info& info() const = 0;

    virtual const std::string& name() const = 0;
    virtual void setName(std::string_view) = 0;

    virtual size_t getImageId() const = 0;
    virtual void setImage(size_t) = 0;

    virtual ~GameEntityInterface() {}

    virtual bool wasUpdated() const = 0;

    virtual ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to);
    friend class LogicProcessorImpl;
};

class GameEntity : virtual public GameEntityInterface {
 private:
    size_t id_;
    std::string name_;
    size_t image_id_ = 0;
    Info info_;
    bool was_updated_ = false;

    void toggleUpdated() override {
        was_updated_ = !was_updated_;
    }

 public:
    GameEntity() = default;
    GameEntity(size_t id) : id_(id) {}
    GameEntity(size_t id, std::string_view name, size_t image_id, const Info& info);

    bool wasUpdated() const override {
        return was_updated_;
    }

    size_t id() const override;

    std::string& info(const std::string&) override;
    const Info& info() const override;

    const std::string& name() const override;
    void setName(std::string_view) override;

    size_t getImageId() const override;
    void setImage(size_t) override;

    void swap(GameEntity& other);
};
}  // namespace DnD
