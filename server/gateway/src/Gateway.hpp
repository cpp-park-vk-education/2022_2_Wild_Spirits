#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast.hpp>

#include <RoomManager.hpp>
#include <UserManager.hpp>
#include <Acceptor.hpp>
#include <Authorizer.hpp>
#include <EventLoop.hpp>
#include <RoomConnector.hpp>
#include <ImageStorage.hpp>

#include <DBQueue.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace fs = std::filesystem;

struct Gateway {
    using connection_ptr_t = std::shared_ptr<UserConnection>;

    BoostEventLoop loop;
    UserManagerImpl user_manager;
    ImageStorage image_storage;
    InMemoryAuthorizer authorizer;
    RoomManagerImpl room_manager;
    RoomConnector room_connector;

    std::shared_ptr<UserAcceptor> acceptor;

    tcp::endpoint endpoint;

    Gateway(const std::string &ip, std::size_t port_num):
        image_storage(fs::path("media")), authorizer(user_manager), room_manager(*this), room_connector(room_manager) {
        auto const address = net::ip::make_address(ip);
        auto const port = static_cast<u_int16_t>(port_num);

        endpoint = tcp::endpoint(address, port);
    }

    void startListening() {
        tcp::acceptor boost_acceptor(loop.get_asio_context());

        beast::error_code ec;
        boost_acceptor.open(endpoint.protocol(), ec);

        if (ec) {
            std::cout << "open error\n";
            std::cout << ec.message() << std::endl;
            exit(1);
        }

        boost_acceptor.bind(endpoint, ec);

        if (ec) {
            std::cout << "bind error\n";
            std::cout << ec.message() << std::endl;
            exit(2);
        }

        boost_acceptor.listen(net::socket_base::max_connections);

        acceptor = std::make_shared<AsioAcceptor>(authorizer, loop, std::move(boost_acceptor));

        acceptor->accept(beast::bind_front_handler(&Gateway::connectToRoom, this));

        start();
    }

    void connectToRoom(connection_ptr_t connection) {
        room_connector.processRequest(connection, beast::bind_front_handler(
                &Gateway::processUserRequest, this));
    }

    void processUserRequest(connection_ptr_t connection) {
        connection->recieve();
    }

    void start(std::size_t threads_cnt=1) {
        // std::vector<std::thread> v;
        // v.reserve(threads_cnt - 1);
        // for(auto i = threads_cnt - 1; i > 0; --i){
        //     v.emplace_back(
        //     [&loop=this->loop]
        //     {
        //         loop.start();
        //     });
        // }
        loop.start();
    }

    void stop() {
        loop.stop();
    }
};