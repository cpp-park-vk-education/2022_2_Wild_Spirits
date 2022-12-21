#include "RoomProcessorEngine.hpp"
#include "nlohmann/json.hpp"


nlohmann::json RoomProcessorEngine::parse(string request){
    using nlohmann::json;
    json request_object = json::parse(request);
    return request_object;
}

RoomProcessorEngine::RoomProcessorEngine(Room::GameLogicProcessor &gameState) : game_state(gameState), change_getter(game_state) {

}

nlohmann::json RoomProcessorEngine::getChanges(nlohmann::json request_object) {
    return nlohmann::json::parse(change_getter.getChangedFields(request_object));
}

