#include "RoomRequestProcessor.hpp"



std::string PlayerCharacters::getPlayerName(unsigned int id){
    return player_table[id];
}

unsigned int PlayerCharacters::getUserId(std::string player_name){
    return id_table[player_name];
}

PlayerCharacters::PlayerCharacters(): player_table(), id_table() {

}

bool RoomSideProcessor::sendDM(string request_string){
    bool state = true;
    room_connection ->sendDM(request_string);
    return state;
}

bool RoomSideProcessor::sendInstance(unsigned int user_id){
    bool state = true;

    return state;
}

bool RoomSideProcessor::broadcast(string request_string){
    bool state = true;
    room_connection ->broadcast(request_string);

    return state;
}

RoomSideProcessor::RoomSideProcessor(Room::GameLogicProcessor &room) : engine(), room(room) {

}

bool RoomSideProcessor::acceptRequest(std::string request_string){

}
