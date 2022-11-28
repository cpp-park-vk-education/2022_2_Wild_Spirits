#pragma once

#include <string>

namespace Gateway{

struct user_id;

using std::string;

class handler;

class ClientConnection{
public:
    void SendReqeuest(string, handler);
    void getImage(string, handler);
};

class Room{
public:
    void sendDM(string);
    void broadcast(string);
    void sendImage(std::string image_id, user_id user);
    void processRequest(user_id, string);
};

}