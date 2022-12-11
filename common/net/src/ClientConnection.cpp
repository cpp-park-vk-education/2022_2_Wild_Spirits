#include <ClientConnection.hpp>

void ClientConnectionImpl::on_recieve(std::string message) {
    recieve();
    recieve_handler(message);
}

std::shared_ptr<ClientConnection> ClientConnectionImpl::createConnection(
                                                        const std::string &address_str,
                                                        u_int16_t port,
                                                        BoostEventLoop &loop,
                                                        recieve_handler_t recieve_handler) {
    auto const address = net::ip::make_address(address_str);
    tcp::endpoint endpoint(address, port);

    tcp::socket socket(loop.get_asio_context());
    socket.connect(endpoint);

    auto ws = std::make_shared<BoostWebSocketStream>(std::move(socket));
    ws->handshake(address_str);

    auto read_buffer = std::make_shared<BoostBuffer>();
    auto write_buffer = std::make_shared<BoostBuffer>();
    auto connection = std::make_shared<BoostWebSocketConnection>(ws, read_buffer, write_buffer);

    return std::make_shared<ClientConnectionImpl>(connection, recieve_handler);
}
