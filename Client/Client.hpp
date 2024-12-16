/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Registry.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <csignal>

#define MAX_LENGTH 1024

namespace RType {
    class Client {
    public:
        Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port);
        ~Client();
        void send(const std::string& message);
        void start_receive();

        void sendExitPacket() {
            std::string exit_message = "DISCONNECTED";
            send(exit_message);
        }
        void run();

    private:
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred);
        void run_receive();
        void render();
        void processEvents();

        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint server_endpoint_;
        std::array<char, MAX_LENGTH> recv_buffer_;
        std::thread receive_thread_;
        boost::asio::io_context& io_context_;
        sf::RenderWindow window;
        bool gameStarted;
        Registry registry;
        Registry::Entity entity_player;
    };
}