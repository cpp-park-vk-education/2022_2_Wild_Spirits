#pragma once

#include <Hasher.hpp>
#include <EventLoop.hpp>

class DBQueue {};

class UserAuthorizer {
private:
    EventLoop &loop;
    DBQueue &db;

public:
    UserAuthorizer(EventLoop&, DBQueue&);
};