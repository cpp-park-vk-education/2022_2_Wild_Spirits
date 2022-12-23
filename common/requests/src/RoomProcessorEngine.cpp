#include "RoomProcessorEngine.hpp"
#include "nlohmann/json.hpp"


nlohmann::json RoomProcessorEngine::parse(string request){
    using nlohmann::json;
    json request_object = json::parse(request);
    return request_object;
}

RoomProcessorEngine::RoomProcessorEngine(DnD::LogicProcessor &gameState, DnD::GameMap& game_map) : game_state(gameState), change_getter(game_state, game_map) {

}

nlohmann::json RoomProcessorEngine::getChanges(nlohmann::json request_object) {
    return nlohmann::json::parse(change_getter.getChangedFields(request_object));
}

std::string RoomProcessorEngine::getInstance() {
    return change_getter.getInstance();
}

