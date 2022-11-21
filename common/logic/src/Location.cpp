#include "Location.hpp"

#include "Position.hpp"
#include "NPC_Instance.hpp"
#include "GameMap.hpp"

Location::Location(std::string_view name, int image_id, const Info& info,
             size_t height, size_t width) :
        GameEntity(name, image_id, info), height_(height), width_(width) {}

void Location::addNPC(size_t id, const NPC& npc, GameMap& map, Position* pos) {}
