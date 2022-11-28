#pragma once
#include <queue>
#include <string>


typedef std::queue<std::deque<std::string>> queue;

class RequestStringParser{
public:
    queue change_queue;
    virtual std::string get_next_change();
    virtual queue make_queue(std::string request_string);
    
private:
    
};

class ClientRequestStringParser: public RequestStringParser{
public:
    std::string get_next_change() override;
    queue make_queue(std::string request_string) override;
private:
    
};


class RoomRequestStringParser: public RequestStringParser{
public:
    std::string get_next_change() override;
    queue make_queue(std::string request_string) override;
private:

};
