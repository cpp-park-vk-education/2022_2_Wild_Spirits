#include <iostream>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast.hpp>

#include <Gateway.hpp>


int main() {
    Gateway gateway("127.0.0.1", 8000);

    gateway.startListening();

    return 0;
}
