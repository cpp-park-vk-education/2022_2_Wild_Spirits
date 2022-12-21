#pragma once

#include <string>

class RequestAcceptor{
public:
    virtual ~RequestAcceptor();
    virtual bool acceptRequest(std::string request_string);
    
};

class RequestSender{
public:
    virtual ~RequestSender();
    virtual bool sendRequest(LM::Request request);
    virtual bool sendRequest(LM::Action action);
};
