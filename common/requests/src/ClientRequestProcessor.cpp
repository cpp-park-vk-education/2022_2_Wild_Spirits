#include "ClientRequestProcessor.hpp"




//Interface methods
bool ClientSideProcessor::acceptRequest(std::string_view request_string){
    bool state = true;
    

    return state;
}

bool ClientSideProcessor::sendRequest(Client::Action action){
    bool state = true;




    return state;
}

bool ClientSideProcessor::sendRequest(Client::Request request) {
    bool state = true;
    switch(request.getType()){
        case Client::Connect:
            break;
        case Client::LoadGameState:

            break;
    }
    return state;
}

ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate, unsigned int client_id) : _client_id(client_id), gamestate(gamestate),
                                                                                                 changer(*new GameStateChanger(gamestate)) {

}

bool ClientSideProcessor::getImage(std::string_view hash, std::shared_ptr<std::string> buffer) {
    bool state = true;
    std::string_view image_view = ImageRequest(hash);
    buffer -> assign(image_view);
    return state;
}

//Internal methods
bool ClientSideProcessor::SendChangesRequest(Client::Action action) {
    return false;
}

bool ClientSideProcessor::ApplyChanges(queue changes_queue) {
    return false;
}

std::string_view ClientSideProcessor::ImageRequest(std::string_view image_hash) {
    std::string_view img_view;
    std::function<void(std::string)> handler = [&img_view](std::string img_string){img_view = img_string;};
    connection -> getImage(image_hash, handler);

    return img_view;
}
