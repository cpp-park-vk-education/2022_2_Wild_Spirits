#pragma once

#include <string>
#include "client_interfaces.hpp"

class RequestAcceptor{
public:
    virtual bool acceptRequest(std::string request_string);
    
};

class RequestSender{
    virtual bool sendRequest(Client::Action action);
};
