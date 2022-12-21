#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>
#include "client_interfaces.hpp"


class HeaderException : public std::runtime_error{
public:
    explicit HeaderException(const std::string& error): std::runtime_error(error.c_str()){

    }
};

enum Header{
    action,
    img_request,
    room_changes,
    apply_request
};

class HeaderSerial{
public:
    std::string operator() (Header header){
        switch (header) {
            case action:
                return "Action";
            case img_request:
                return "ImageRequest";
            case room_changes:
                return "RoomChanges";
            case apply_request:
                return "RequestApply";
        }
        return {};
    }
    Header operator() (const std::string& header_string){
        if(header_string == "Action"){
            return Header::action;
        }
        else if(header_string == "ImageRequest"){
            return Header::img_request;
        }
        else if(header_string == "RoomChanges"){
            return Header::room_changes;
        }
        else if(header_string == "RequestApply"){
            return Header::apply_request;
        }
        else{
            throw HeaderException("Invalid Header description");
        }
    }
    Client::ActionType getHeader(const std::string& action_header_string){
        if (action_header_string == "UseWeapon"){
            return Client::kUseWeapon;
        }
        else if(action_header_string == "UseConsumable"){
            return Client::kUseConsumable;
        }
        else if(action_header_string == "UseSkill"){
            return Client::kUseSkill;
        }
        else if(action_header_string == "UseSpell"){
            return Client::kUseSpell;
        }
        else{
            throw HeaderException("Invalid Header description");
        }
    }
    std::string operator() (Client::ActionType type){
        switch (type) {
            case Client::kUseWeapon:
                return "UseWeapon";
            case Client::kUseConsumable:
                return "UseConsumable";
            case Client::kUseSkill:
                return "UseSkill";
            case Client::kUseSpell:
                return "UseSpell";
        }
        return {};
    }
};

