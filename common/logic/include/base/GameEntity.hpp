#pragma once

#include <unordered_map>
#include <string>

class GameEntityInterface {
 public:
    virtual const std::string& info(const std::string&) const = 0;
    virtual std::string& info(const std::string&) = 0;

    virtual const std::string& name() const = 0;
    virtual void setName(std::string_view) = 0;

    virtual int getImageId() const = 0;
    virtual void setImage(int) = 0;
};

class GameEntity : public GameEntityInterface {
 public:
    using Info = std::unordered_map<std::string, std::string>;

 private:
    std::string name_;
    int image_id_;
    Info info_;

 public:
    GameEntity() = default;
    GameEntity(std::string_view name, int image_id, const Info& info);

    const std::string& info(const std::string&) const override;

    std::string& info(const std::string&) override;

    const std::string& name() const override;
    void setName(std::string_view) override;

    int getImageId() const override;
    void setImage(int) override;
};
