#pragma once
#include <queue>
#include <string>


typedef std::queue<std::deque<std::string>> queue;

class RequestStringParser{
public:
    RequestStringParser();
    queue change_queue;
    virtual std::string get_next_change();
    virtual queue make_queue(std::string request_string);
    
private:
    
};

class ClientRequestStringParser: public RequestStringParser{
public:
    ClientRequestStringParser();
    std::string get_next_change() override;
    queue make_queue(std::string request_string) override;
private:
    
};


class RoomRequestStringParser: public RequestStringParser{
public:
    RoomRequestStringParser();
    std::string get_next_change() override;
    queue make_queue(std::string request_string) override;
private:

};
