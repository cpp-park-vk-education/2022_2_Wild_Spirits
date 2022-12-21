#include "ChangeGetter.hpp"

void ChangeGetter::load_collector(change_queue changes){

}

ChangeGetter::ChangeGetter(ChangeCollector &collector, DnD::LogicProcessor &gameState): handlers(), game_state(gameState), collector(collector)  {
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<WeaponHandler>());
    handlers.push_back(std::make_unique<ConsumableHandler>());
    handlers.push_back(std::make_unique<SkillHandler>());
    handlers.push_back(std::make_unique<SpellHandler>());
}

void ChangeGetter::load_collector(string change) {

}

std::string ChangeGetter::getChangedFields(nlohmann::json request_part) {
    for(std::unique_ptr<ChangeHandler>& handler : handlers){
        if(handler ->CanHandle(request_part)){
            return handler ->Handle(request_part, game_state);
        }
    }
}





