#pragma once

#include <string>
#include "client_interfaces.hpp"

class RequestAcceptor{
public:
    virtual ~RequestAcceptor();
    virtual bool acceptRequest(std::string_view request_string);
    
};

class RequestSender{
public:
    virtual ~RequestSender();
    virtual bool sendRequest(Client::Request request);
    virtual bool sendRequest(Client::Action action);
};
