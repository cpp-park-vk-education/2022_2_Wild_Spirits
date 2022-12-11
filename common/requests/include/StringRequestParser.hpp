#pragma once
#include <queue>
#include <string>
#include <tuple>


typedef std::deque<std::tuple<std::string, std::string>> queue;

class RequestStringParser{
public:
    RequestStringParser();
    queue change_queue;
    virtual std::string get_next_change() = 0;
    virtual queue make_queue(std::string request_string) = 0;
    
private:
    
};

class ClientRequestStringParser: public RequestStringParser{
public:
    ClientRequestStringParser();
    std::string get_next_change() override;
    queue make_queue(std::string request_string) override;
    bool has_changes() const;
private:
    
};


class RoomRequestStringParser: public RequestStringParser{
public:
    RoomRequestStringParser();
    std::string get_next_change() override;

    queue make_queue(std::string request_string) override;

private:

};
