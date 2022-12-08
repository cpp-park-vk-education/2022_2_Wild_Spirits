#include "ClientRequestProcessor.hpp"


bool ClientSideProcessor::acceptRequest(std::string request_string){
    bool state = true;


    return state;
}

bool ClientSideProcessor::sendRequest(Client::Action action){
    bool state = true;


    return state;
}

ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate) : gamestate(gamestate),
                                                                         changer(gamestate) {

}
