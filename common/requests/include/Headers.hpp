#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>

#include <Actions/Action.h>

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
    LM::Action::Type getHeader(const std::string& action_header_string){
        if (action_header_string == "UseWeapon"){
            return LM::Action::Type::kUseWeapon;
        }
        else if(action_header_string == "UseConsumable"){
            return LM::Action::Type::kUseConsumable;
        }
        else if(action_header_string == "UseSkill"){
            return LM::Action::Type::kUseSkill;
        }
        else if(action_header_string == "UseSpell"){
            return LM::Action::Type::kUseSpell;
        }
        else{
            throw HeaderException("Invalid Header description");
        }
    }
    std::string operator() (LM::Action::Type type){
        switch (type) {
            case LM::Action::Type::kUseWeapon:
                return "UseWeapon";
            case LM::Action::Type::kUseConsumable:
                return "UseConsumable";
            case LM::Action::Type::kUseSkill:
                return "UseSkill";
            case LM::Action::Type::kUseSpell:
                return "UseSpell";
        }
        return {};
    }
};

