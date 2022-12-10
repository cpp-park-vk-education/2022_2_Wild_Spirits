#include <iostream>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast.hpp>

#include <RoomManager.hpp>
#include <UserManager.hpp>
#include <Acceptor.hpp>
#include <EventLoop.hpp>
#include <RoomConnector.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

int main() {
    BoostEventLoop loop;
    UserManagerImpl user_manager;
    RoomManagerImpl room_manager;

    RoomConnector room_connector(room_manager);

    tcp::acceptor acceptor(loop.get_asio_context());

    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<u_int16_t>(8000);

    tcp::endpoint endpoint {address, port};

    beast::error_code ec;
    acceptor.open(endpoint.protocol(), ec);

    if (ec) {
        std::cout << "open error\n";
    }

    acceptor.bind(endpoint, ec);

    if (ec) {
        std::cout << "bind error\n";
    }

    acceptor.listen(net::socket_base::max_connections);

    AsioAcceptor asio_acceptor(user_manager, loop, std::move(acceptor));

    asio_acceptor.accept([&room_connector](std::shared_ptr<UserConnection> connection) {
        // connection->recieve();
        room_connector.processRequest(connection, [](std::shared_ptr<UserConnection> connection)
        {
            connection->recieve();
        });
    });

    loop.start();

    return 0;
}
