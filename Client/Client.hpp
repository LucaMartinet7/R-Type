/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <array>

#define MAX_LENGTH 1024

namespace RType {
    class Client {
    public:
        Client(boost::asio::io_context& io_context, const std::string& host, short port);
        ~Client();
        void send(const std::string& message);
        void receive();

    private:
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred);

        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint server_endpoint_;
        boost::asio::ip::udp::endpoint sender_endpoint_;
        std::array<char, MAX_LENGTH> recv_buffer_;
    };
}