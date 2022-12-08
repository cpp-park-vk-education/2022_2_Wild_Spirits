#include "ClientRequestProcessor.hpp"




//Interface methods
bool ClientSideProcessor::acceptRequest(std::string request_string){
    bool state = true;


    return state;
}

bool ClientSideProcessor::sendRequest(Client::Action action){
    bool state = true;




    return state;
}

ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate, unsigned int client_id) : _client_id(client_id), gamestate(gamestate),
                                                                                                 changer(*new GameStateChanger(gamestate)) {

}



//Internal methods
bool ClientSideProcessor::SendChangesRequest(Client::Action action) {
    return false;
}

bool ClientSideProcessor::ApplyChanges(queue changes_queue) {
    return false;
}

bool ClientSideProcessor::ImageRequest(std::string image_hash) {
    return false;
}
