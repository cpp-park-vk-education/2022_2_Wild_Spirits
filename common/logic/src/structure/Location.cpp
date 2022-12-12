#include "Location.hpp"

#include "Position.hpp"
#include "NPC_Instance.hpp"
#include "GameMap.hpp"

namespace DnD {
Location::Location(size_t id, std::string_view name, int image_id,
                   size_t height, size_t width, const Info& info) :
        GameEntity(id, name, image_id, info), height_(height), width_(width) {}

ErrorStatus Location::setCharacteristic(const std::string& which, const SetterParam& to) {
    auto status = GameEntity::setCharacteristic(which, to);
    if (status != ErrorStatus::INVALID_SETTER) {
        return status;
    }

    auto value = std::get_if<int64_t>(&to);
    if (!value) {
        return ErrorStatus::INVALID_ARGUMENT;
    }

    if (which == "width") {
        setWidth(*value);
        return ErrorStatus::OK;
    } else if (which == "height") {
        setHeight(*value);
        return ErrorStatus::OK;
    }

    return ErrorStatus::INVALID_SETTER;
}
}  // namespace DnD
