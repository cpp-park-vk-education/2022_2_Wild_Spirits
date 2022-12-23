#pragma once

#include <string>

#include <Actions/Action.h>

class RequestAcceptor{
public:
    virtual ~RequestAcceptor(){}
    virtual bool acceptRequest(std::string request_string) = 0;
    
};

class RequestSender{
public:
    virtual ~RequestSender(){}
    virtual bool sendRequest(LM::Action& action) = 0;
};
