#pragma once

#include <string>
#include <boost/beast.hpp>

class Buffer {
public:
    virtual std::string data() = 0;
    virtual void setData(const std::string &) = 0;
};

class BoostBuffer: public Buffer {
private:
    boost::beast::flat_buffer buffer;

public:
    BoostBuffer() = default;
    explicit BoostBuffer (const std::string&);

    virtual ~BoostBuffer() {}

    virtual std::string data() override;
    virtual void setData(const std::string &) override;

    boost::beast::flat_buffer &get_underlying_buffer();
    const boost::beast::flat_buffer &get_underlying_buffer() const;

    void clear();
};