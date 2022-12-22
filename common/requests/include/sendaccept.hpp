#pragma once

#include <string>

#include <Actions/Action.h>

class RequestAcceptor{
public:
    virtual ~RequestAcceptor();
    virtual bool acceptRequest(std::string request_string);
    
};

class RequestSender{
public:
    virtual ~RequestSender();
    virtual bool sendRequest(LM::Action action);
};
