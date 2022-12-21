#include "GameStateChanger.hpp"



bool GameStateChanger::makechange(std::tuple<std::size_t, std::string, std::string> setter_params){
    bool state = true;
    


    return state;
}

GameStateChanger::GameStateChanger(DnD::GameState &gamestate) : gamestate(gamestate), handlers() {
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
