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
    BoostBuffer() = default;
    explicit BoostBuffer (const std::string&);

    virtual std::string data() override;

    boost::beast::flat_buffer &get_underlying_buffer() {
        return buffer;
    }

    const boost::beast::flat_buffer &get_underlying_buffer() const {
        return buffer;
    }

    void clear();
};