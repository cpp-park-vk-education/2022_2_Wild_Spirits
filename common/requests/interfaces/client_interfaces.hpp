#pragma once
#include <iostream>
#include "Activatable.hpp"


namespace Client{
    class Room{};
    enum ActionType{
        kUseWeapon,
        kUseConsumable,
        kUseSkill,
        kUseSpell
    };
    enum RequestType{
        Connect,
        LoadGameState
    };

    class Request{
        RequestType type;
    public:
        RequestType getType() const{
            return type;
        }
    };



    class Action{
        std::size_t getX(); // useAction moveAction
        std::size_t getY(); // useAction moveAction
        DnD::Activatable& getActivatable(); //Activatable
        
        ActionType _type;
    public:

        ActionType getType(){
            return  _type;
        }
    };
    class GameState;
    enum Header{
        action,
        img_request,
        room_changes,
        dm_changes,
        apply_request
        };
}