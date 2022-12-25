#include "GameStateChanger.hpp"
#include <memory>

#include <Demo.hpp>

GameStateChanger::GameStateChanger(DnD::GameState &_gamestate, DnD::GameMap &game_map) : gamestate(_gamestate), handlers(), game_map(game_map) {
    handlers.push_back(std::make_unique<ImageHandler>());
    handlers.push_back(std::make_unique<NameHandler>());
    handlers.push_back(std::make_unique<InfoHandler>());
    handlers.push_back(std::make_unique<CastTypeHandler>());
    handlers.push_back(std::make_unique<ScalingHandler>());
    handlers.push_back(std::make_unique<ActivationCostHandler>());
    handlers.push_back(std::make_unique<HpMaxHandler>());
    handlers.push_back(std::make_unique<ApMaxHandler>());
    handlers.push_back(std::make_unique<BaseArmorHandler>());
    handlers.push_back(std::make_unique<StatsHandler>());
    handlers.push_back(std::make_unique<SkillsHandler>());
    handlers.push_back(std::make_unique<ApHandler>());
    handlers.push_back(std::make_unique<HpHandler>());
    handlers.push_back(std::make_unique<ArmorHandler>());
    handlers.push_back(std::make_unique<PositionHandler>());
    handlers.push_back(std::make_unique<HostileHandler>());
    handlers.push_back(std::make_unique<XPHandler>());
    handlers.push_back(std::make_unique<CastCostHandler>());
    handlers.push_back(std::make_unique<UsesHandler>());
}


bool GameStateChanger::makechange(nlohmann::json request_part) {
    std::cout << "MAKING CHANGE with the request_part :\t" << request_part << std::endl;
    for(std::unique_ptr<ChangeHandler>& handler : handlers){
        if(handler ->CanHandle(request_part)){
            std::cout << "=========HANDLING=========" << std::endl;
            handler ->SetField(request_part, gamestate, game_map);
        }   
    }
    return true;
}
