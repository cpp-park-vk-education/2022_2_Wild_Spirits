#include <iostream>
#include <fstream>
#include <thread>  //NOLINT 

#include <boost/asio.hpp>

#include <EventLoop.hpp>
#include <WebSocketStream.hpp>
#include <ClientConnection.hpp>

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

int main() {
    BoostEventLoop loop;

    auto connection = ClientConnectionImpl::createConnection("127.0.0.1", 8000, loop,
                    [](const std::string &message) {
                        std::cout << "recieved: " << message << std::endl;
                    });

    connection->recieve();

    std::thread loop_thread([&loop](){
        loop.start();
    });

    std::string input;
    std::getline(std::cin, input);

    while (input != "end") {
        if (input == "send") {
            std::ifstream file("base64.txt");

            std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            connection->async_write(file_contents, [](){
                std::cout << "sent file" << std::endl;
            });
        } else {
            connection->async_write(input, [&input](){
                std::cout << "wrote " << input << std::endl;
            });
        }

        std::getline(std::cin, input);
    }

    connection->close([&loop, &loop_thread]{
        loop.stop();
    });

    loop_thread.join();

    return 0;
}
