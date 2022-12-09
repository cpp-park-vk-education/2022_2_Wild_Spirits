#pragma once




namespace Client{

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