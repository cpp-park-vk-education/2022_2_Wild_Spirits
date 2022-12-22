#include "ChangeGetter.hpp"

void ChangeGetter::load_collector(change_queue changes){

}

ChangeGetter::ChangeGetter(ChangeCollector &collector, DnD::LogicProcessor &gameState, DnD::GameMap& gameMap): handlers(), game_state(gameState),game_map(gameMap), collector(collector) , loading_instances() {
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<WeaponHandler>());
    handlers.push_back(std::make_unique<ConsumableHandler>());
    handlers.push_back(std::make_unique<SkillHandler>());
    handlers.push_back(std::make_unique<SpellHandler>());

    loading_instances.emplace_back("npc");
    loading_instances.emplace_back("allCharacters");
    loading_instances.emplace_back("items");
    loading_instances.emplace_back("activatableItems");
    loading_instances.emplace_back("weapons");
    loading_instances.emplace_back("spells");
    loading_instances.emplace_back("armor");
    loading_instances.emplace_back("races");
    loading_instances.emplace_back("classes");
    loading_instances.emplace_back("players");
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

std::string ChangeGetter::getInstance(){
    using nlohmann::json;
    json instance_object;
    NPCLoader npc_loader;
    npc_loader.Load(game_state, instance_object);
    activatableItemsLoader ai_loader;
    ai_loader.Load(game_state, instance_object);
    allCharactersLoader char_loader;
    char_loader.Load(game_state, instance_object);
    itemsLoader items_loader;
    items_loader.Load(game_state, instance_object);
    weaponsLoader weapons_Loader;
    weapons_Loader.Load(game_state, instance_object);
    spellsLoader spells_loader;
    spells_loader.Load(game_state, instance_object);
    armorLoader armor_loader;
    armor_loader.Load(game_state, instance_object);
    return instance_object.dump();
}
