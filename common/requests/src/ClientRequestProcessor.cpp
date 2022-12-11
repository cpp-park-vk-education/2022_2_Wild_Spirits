#include "ClientRequestProcessor.hpp"
#include



//Interface methods
bool ClientSideProcessor::acceptRequest(string request_string){
    bool state = true;
    switch(getHeader(request_string)){

        case action:
            throw HeaderException("Invalid header for accept");
        case img_request:
            throw HeaderException("Invalid header for accept");
        case room_changes:
            state = ApplicationRequest(engine.getSetterQueue(request_string));
            break;
        case apply_request:
            state = ApplyChanges(request_string);
            break;
    }
    return state;
}

bool ClientSideProcessor::sendRequest(Client::Action action){

    return SendChangesRequest(action);

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

bool ClientSideProcessor::getImage(std::string_view hash, std::shared_ptr<std::string> image_string_buffer) {
    bool state = true;
    std::string_view image_view = ImageRequest(hash);
    image_string_buffer -> assign(image_view);
    return state;
}

//Internal methods
bool ClientSideProcessor::SendChangesRequest(Client::Action action) {

    bool state = true;

    std::string action_string = engine.handler->actionString(action);
    Client::ActionType header = action.getType();
    std::function<void(bool)> handler = [&state](bool status){state = status;}; //TODO:Сделать коды ответа в handler
    connection -> SendReqeuest(engine.getRequestString(action_string, header), handler);
    return state;
}

bool ClientSideProcessor::ApplyChanges(string changes) {
    bool state = true;
    queue setters = engine.getSetterQueue(changes);
    while(!setters.empty()){
        state &= changer.makechange(setters.front());
        setters.pop_front();
    }
    return state;
}

std::string_view ClientSideProcessor::ImageRequest(std::string_view image_hash) {
    std::string_view img_view;
    std::function<void(std::string)> handler = [&img_view](std::string img_string){img_view = img_string;};
    connection -> getImage(image_hash, handler);
    return img_view;
}
//Interface methods
bool ClientSideProcessor::Connection(std::string ip, std::string port) {

    return false;
}

std::size_t ClientSideProcessor::CreateRoom() {
    return false;
}

bool ClientSideProcessor::StartGame() {
    return false;
}

bool ClientSideProcessor::ApplicationRequest(queue changes) {
    bool state = true;
    buffer.setChanges(changes);
    return state;
}

Header ClientSideProcessor::getHeader(std::string) {
    return img_request;
}

bool ClientSideProcessor::checkUnappliedChanges() const {
    return buffer.hasUnappliedChanges();
}



bool ClientSideProcessor::ConnectToRoom() {
    return false;
}

ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate): is_connected(false), _client_id(), engine(), connection(), gamestate(gamestate),
                                                                        changer(gamestate), buffer(){

}


