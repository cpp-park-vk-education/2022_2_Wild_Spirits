#include "RoomRequestProcessor.hpp"
#include "nlohmann/json.hpp"
#include "Headers.hpp"

#include <Room.hpp>


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
    room_connection.sendDM(request_string);
    return state;
}

bool RoomSideProcessor::sendInstance(unsigned int user_id){
    bool state = true;
    room_connection.sendUser(user_id, engine.getInstance());
    return state;
}

bool RoomSideProcessor::broadcast(string request_string){
    bool state = true;
    room_connection.broadcast(request_string);
    return state;
}

bool RoomSideProcessor::broadcast() {
    bool state = true;
    room_connection.broadcast(engine.getInstance());
    return state;
}

RoomSideProcessor::RoomSideProcessor(Room &room_connection, DnD::LogicProcessor &room, DnD::GameMap& game_map): room_connection(room_connection), room(room), engine(room, game_map) {}

bool RoomSideProcessor::acceptRequest(std::string request_string){
    using nlohmann::json;
    HeaderSerial deserializer;
    json request = engine.parse(request_string);
    if(request_string == "!startgame"){
        broadcast();
        return true;
    }
    if(deserializer(std::string(request["header"])) == Header::action){
        sendDM(engine.Gen().makeRequestString(engine.getChanges(request).dump(), deserializer(Header::room_changes)));
    }
    return true;
}
