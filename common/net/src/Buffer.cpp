#include <Buffer.hpp>

BoostBuffer::BoostBuffer(const std::string &str) {
    boost::beast::ostream(buffer) << str;
}

std::string BoostBuffer::data() {
    return boost::beast::buffers_to_string(buffer.data());
}

void BoostBuffer::clear() {
    buffer.consume(buffer.size());
}
