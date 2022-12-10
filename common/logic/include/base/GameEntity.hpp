#pragma once

#include <unordered_map>
#include <string>

namespace DnD {
class GameEntityInterface {
 protected:
    using Info = std::unordered_map<std::string, std::string>;

 private:
    virtual void toggleUpdated() = 0;
    virtual bool wasUpdated() const = 0;

 public:
    virtual std::string& info(const std::string&) = 0;
    virtual const Info& info() const = 0;

    virtual const std::string& name() const = 0;
    virtual void setName(std::string_view) = 0;

    virtual size_t getImageId() const = 0;
    virtual void setImage(size_t) = 0;

    virtual size_t id() const = 0;

    friend class LogicProcessorImpl;
};

class GameEntity : public GameEntityInterface {
 private:
    size_t id_;
    std::string name_;
    size_t image_id_;
    Info info_;
    bool was_updated_ = false;

    void toggleUpdated() override {
        was_updated_ = !was_updated_;
    }

    bool wasUpdated() const override {
        return was_updated_;
    }

 public:
    GameEntity() = default;
    GameEntity(size_t id, std::string_view name, size_t image_id, const Info& info);

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
