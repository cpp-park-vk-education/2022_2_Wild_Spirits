#pragma once

#include <string>
#include <boost/system.hpp>

class ErrorCode {
public:
    virtual int value() = 0;
    virtual std::string message() = 0;
};

class BoostErrorCode: public ErrorCode {
private:
    boost::system::error_code ec;

public:
    virtual int value() override;
    virtual std::string message() override;
};
