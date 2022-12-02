#include "Location.hpp"

#include "Position.hpp"
#include "NPC_Instance.hpp"
#include "GameMap.hpp"

namespace DnD {
Location::Location(size_t id, std::string_view name, int image_id,
                   size_t height, size_t width, const Info& info) :
        GameEntity(id, name, image_id, info), height_(height), width_(width) {}
}  // namespace DnD
