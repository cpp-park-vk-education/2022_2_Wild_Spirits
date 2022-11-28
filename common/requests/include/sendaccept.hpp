#pragma once

#include <string>

class RequestAcceptor{
public:
    virtual bool acceptRequest(std::string);
    
};

class RequestSender{
    virtual bool sendRequest();
};
