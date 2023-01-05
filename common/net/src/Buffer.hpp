#pragma once

#include <string>
#include <boost/beast.hpp>

class Buffer {
public:
    virtual std::string data() = 0;
};

class BoostBuffer: public Buffer {
private:
    boost::beast::flat_buffer buffer;

public:
    virtual std::string data() override;
};