#pragma once

#include <string>

namespace Gateway{

struct user_id;

using std::string;

class handler;

class ClientConnection{
public:
    void SendReqeuest(string request, handler gateway_handler);
    void getImage(string request, handler gateway_handler);
};

class Room{
public:
    void sendDM(string request);
    void broadcast(string request);
    void sendImage(std::string image_id, user_id user);
    void processRequest(user_id user, string request);
};

}