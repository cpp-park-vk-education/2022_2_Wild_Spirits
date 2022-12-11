#pragma once

#include <string>

namespace Gateway{

struct user_id;

using std::string;


class ClientConnection{
public:
    void SendReqeuest(string request,std::function<void(bool)> gateway_handler);
    void getImage(std::string_view request, std::function<void(std::string)> gateway_handler);
};

class Room{
public:
    void sendDM(string request);
    void broadcast(string request);
    void sendImage(std::string image_id, user_id user);
    void processRequest(user_id user, string request);
};

}