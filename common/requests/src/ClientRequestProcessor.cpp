#include "ClientRequestProcessor.hpp"
#include "GameState.hpp"
#include "boost/asio.hpp"
#include "nlohmann/json.hpp"


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
    return false;
}

std::string ClientSideProcessor::sendRequest(std::string request){
    bool state = true;
    std::string response_buffer;
    std::function<void(bool)> handler = [&state](bool answer){
        state = answer;
    };
    connection ->SendReqeuest(request, handler);
    return response_buffer;
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


bool ClientSideProcessor::getImage(std::string_view hash, std::shared_ptr<std::string> image_string_buffer) {
    bool state = true;
    std::string_view image_view = ImageRequest(hash);
    image_string_buffer -> assign(image_view);
    return state;
}

//Internal methods
//bool ClientSideProcessor::SendChangesRequest(Client::Action action) {
//
//    bool state = true;
////
////    std::string action_string = engine.handler->actionString(action);
//    Client::ActionType header = action.getType();
//    std::function<void(bool)> handler = [&state](bool status){state = status;}; //TODO: Сделать коды ответа в handler
////    connection -> SendReqeuest(engine.getRequestString(action_string, header), handler);
//    return state;
//}

bool ClientSideProcessor::SendChangesRequest(LM::Action action) {

    bool state = true;
    std::string action_string = engine.handler->actionString(action);
    std::function<void(bool)> handler = [&state](bool status){state = status;}; //TODO: Сделать коды ответа в handler
    connection -> SendReqeuest(engine.getRequestString(action_string, Header::action), handler);
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
    bool state = true;
    connection = std::make_shared<Gateway::ClientConnection>(ip, port, loop, [this, &state](std::string message){
        state = acceptRequest(message);
    });
    return state;
}

Client::Room ClientSideProcessor::CreateRoom() {
    std::string creating_request = "create_room";
    sendRequest(creating_request);
    return {};
}

bool ClientSideProcessor::StartGame() {
    return false;
}

bool ClientSideProcessor::ApplicationRequest(queue changes) {
    bool state = true;
    buffer.setChanges(changes);
    return state;
}

Header ClientSideProcessor::getHeader(std::string request) {
    HeaderSerial deserializer;
    json request_obj = json::parse(request);
    return deserializer(request_obj.begin().key());
}

bool ClientSideProcessor::checkUnappliedChanges() const {
    return buffer.hasUnappliedChanges();
}



bool ClientSideProcessor::ConnectToRoom(Client::Room room) {
    return false;
}

bool ClientSideProcessor::isAuthorized() const {
    return is_authorized;
}

bool ClientSideProcessor::Login(std::string, std::string password) {
    return false;
}

bool ClientSideProcessor::Register(std::string login, std::string password) {
    return false;
}

ClientSideProcessor::ClientSideProcessor(DnD::GameState &gamestate, DnD::GameMap &map, DnD::TurnOrder &order): gamestate(gamestate),
                                                                                                               changer(gamestate), _map(map), _order(order) {

}

bool ClientSideProcessor::sendRequest(LM::Action action) {
    return SendChangesRequest(action);
}

//ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate): is_connected(false), _client_id(), engine(), connection(), gamestate(gamestate),
//                                                                        changer(gamestate), buffer(){
//
//}


