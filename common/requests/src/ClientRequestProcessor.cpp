#include "ClientRequestProcessor.hpp"


bool ClientSideProcessor::acceptRequest(std::string request_string){

}

bool ClientSideProcessor::sendRequest(Client::Action action){
    
}

ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate) : gamestate(gamestate),
                                                                         GameStateChanger(gamestate) {

}
