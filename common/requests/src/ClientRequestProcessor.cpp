#include "ClientRequestProcessor.hpp"
#include "GameState.hpp"
#include "boost/asio.hpp"
#include "nlohmann/json.hpp"
#include "sstream"

#include <iostream>

// Interface methods
bool ClientSideProcessor::acceptRequest(string request_string) {
    bool state = true;

    std::cout << "request_string: " << request_string << std::endl;
    if (request_string.starts_with("room_id")) {
        _room_id = stoi(request_string.substr(request_string.find(":") + 1));
        return true;
    }
    if (request_string == "Registered successfully") {
        setAuthorized();
        std::cout << "AR\n";
        barrier.arrive();
        return true;
    }
    if (request_string == "Authorized successfully") {
        setAuthorized();
        std::cout << "AR\n";
        barrier.arrive();
        return true;
    }
    if (request_string.starts_with("Authorization error")) {
        setUnAuthorized();
        std::cout << "AR\n";
        barrier.arrive();
        return false;
    }
    switch (getHeader(request_string)) {
        
        case action: throw HeaderException("Invalid header for accept");
        case img_request: throw HeaderException("Invalid header for accept");
        case room_changes: state = ApplicationRequest(engine.getSetterQueue(request_string)); break;
        case apply_request: state = ApplyChanges(request_string); barrier.arrive(); break;
    }
    return state;
}

bool ClientSideProcessor::sendRequest(LM::Action& action) { return SendChangesRequest(action); }

std::string ClientSideProcessor::sendRequest(std::string request) {
    std::cout << "sending: " << request << std::endl;
    bool state = true;
    std::string response_buffer;
    connection->sendMessage(request, [](bool answer) { std::cout << "answer: " << answer << std::endl; });
    return response_buffer;
}

bool ClientSideProcessor::getImage(std::string_view hash, std::shared_ptr<std::string> image_string_buffer) {
    bool state = true;
    std::string_view image_view = ImageRequest(hash);
    image_string_buffer->assign(image_view);
    return state;
}

// Internal methods

bool ClientSideProcessor::SendChangesRequest(LM::Action& action) {

    bool state = true;
    std::string action_string = engine.handler->actionString(action);
    std::function<void(bool)> handler = [&state](bool status) {
        state = status;
    };    // TODO: Сделать коды ответа в handler
    connection->sendMessage(engine.getRequestString(action_string, Header::action), handler);
    return state;
}

bool ClientSideProcessor::ApplyChanges(string changes) {
    bool state = true;
    std::deque<nlohmann::json> setters = engine.getAnotherSetterQueue(changes);
    while (!setters.empty()) {
        json temp;
        // state &= changer.makechange(temp[std::get<0>(setters.front())] = std::get<1>(setters.front()));
        state &= changer.makechange(setters.front());
        setters.pop_front();
    }
    return state;
}

std::string_view ClientSideProcessor::ImageRequest(std::string_view image_hash) {
    std::string_view img_view;
    std::function<void(std::string)> handler = [&img_view](std::string img_string) { img_view = img_string; };
    HeaderSerial s;
    connection->sendMessage(
        engine.generator->makeRequestString(std::string(image_hash), s(Header::img_request)),
        [](bool status) {

        });
    return img_view;
}
// Interface methods
bool ClientSideProcessor::Connection(std::string ip, std::string port) {
    bool state = true;
    // connection = std::make_shared<ClientConnectionImpl>(ip, port, loop,
    // std::function<void(std::string)>([this, &state](std::string message){
    //     state = acceptRequest(message);
    // }));
    connection = ClientConnectionImpl::createConnection(
        ip, std::stoi(port), loop, [this](std::string message) { acceptRequest(message); });
    return state;
}

LM::Room ClientSideProcessor::CreateRoom() {
    std::string creating_request = "create";
    sendRequest(creating_request);
    return LM::Room({ _room_id });
}

bool ClientSideProcessor::StartGame() {
    sendRequest("!startgame");
    barrier.arrive_and_wait();
    return true;
}

bool ClientSideProcessor::ApplicationRequest(queue changes) {
    bool state = true;
    buffer.setChanges(changes);
    return state;
}

Header ClientSideProcessor::getHeader(std::string request) {
    HeaderSerial deserializer;
    nlohmann::json request_obj = nlohmann::json::parse(request);
    // return deserializer(request_obj.begin().key());
    std::cout << "getting header by view: " << request_obj["header"] << std::endl;
    return deserializer(std::string(request_obj["header"]));
}

bool ClientSideProcessor::checkUnappliedChanges() const { return buffer.hasUnappliedChanges(); }

bool ClientSideProcessor::ConnectToRoom(LM::Room room) { return false; }

bool ClientSideProcessor::isAuthorized() const { return is_authorized; }

bool ClientSideProcessor::Login(std::string login, std::string password) {
    std::stringstream ss;
    ss << "login:" << login << ":" << password;
    sendRequest(ss.str());
    std::cout << "AR WT\n";
    barrier.arrive_and_wait();
    return isAuthorized();
}

bool ClientSideProcessor::Register(std::string login, std::string password) {
    std::stringstream ss;
    ss << "register:" << login << ":" << password;
    sendRequest(ss.str());
    std::cout << "AR WT\n";
    barrier.arrive_and_wait();
    return isAuthorized();
}

ClientSideProcessor::ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order)
    : gamestate(gamestate),
      changer(gamestate, map),
      _map(map),
      _order(order),
      _room_id(0){ }

std::vector<LM::Room> ClientSideProcessor::GetRooms() { return std::vector<LM::Room>(); }

void ClientSideProcessor::setAuthorized() { is_authorized = true; }

void ClientSideProcessor::setUnAuthorized() { is_authorized = false; }

// bool ClientSideProcessor::sendRequest(LM::Action &action) {
//     return SendChangesRequest(action);
// }

// ClientSideProcessor::ClientSideProcessor(Client::GameState &gamestate): is_connected(false), _client_id(),
// engine(), connection(), gamestate(gamestate),
//                                                                         changer(gamestate), buffer(){
//
// }

void ClientSideProcessor::start() {
    connection->recieve();

    loop_thread = std::jthread([this]() { loop.start(); });
}

void ClientSideProcessor::stop() {
    connection->close([this] { loop.stop(); });

    loop_thread.join();
}


void ClientSideProcessor::setUpToDate(){
    buffer.setUpToDate();
}


const InterlayerBuffer& ClientSideProcessor::getChangesBuffer(){
    return buffer;
}