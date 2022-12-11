#include <Buffer.hpp>

BoostBuffer::BoostBuffer(const std::string &str) {
    boost::beast::ostream(buffer) << str;
}

std::string BoostBuffer::data() {
    return boost::beast::buffers_to_string(buffer.data());
}

void BoostBuffer::setData(const std::string &data) {
    clear();
    boost::beast::ostream(buffer) << data;
}

void BoostBuffer::clear() {
    buffer.consume(buffer.size());
}

boost::beast::flat_buffer &BoostBuffer::get_underlying_buffer() {
    return buffer;
}

const boost::beast::flat_buffer &BoostBuffer::get_underlying_buffer() const {
    return buffer;
}
