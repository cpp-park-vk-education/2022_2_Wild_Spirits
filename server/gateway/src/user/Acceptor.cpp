#include <Acceptor.hpp>

AsioAcceptor::AsioAcceptor(UserManager &manager, BoostEventLoop &loop, tcp::acceptor &&acceptor):
    UserAcceptor(manager), loop(loop), acceptor(std::move(acceptor)) {}

void AsioAcceptor::accept(acceptor_handler handler) {
    acceptor.async_accept(loop.get_asio_context(), [this, handler](beast::error_code ec, tcp::socket socket) {
        on_accept(ec, std::move(socket), handler);
    });
}

void AsioAcceptor::on_accept(beast::error_code ec, tcp::socket socket, acceptor_handler handler) {
    ws_ptr_t ws = std::make_shared<BoostWebSocketStream>(std::move(socket));

    ws->async_accept_handshake([this, ws, handler](beast::error_code ec){
        on_handshake(ws, ec, handler);
    });

    accept(handler);
}

void AsioAcceptor::on_handshake(ws_ptr_t ws, beast::error_code ec, acceptor_handler handler) {
    auto buffer = std::make_shared<BoostBuffer>();
    auto connection = std::make_shared<BoostWebSocketConnection>(std::move(ws), std::move(buffer));


    authorizer.authorize_user(connection, handler);
}
