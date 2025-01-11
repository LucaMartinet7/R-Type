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
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <csignal>
#include "../Server/Network/Packet.hpp"

#define MAX_LENGTH 1024

namespace RType {
    enum class SpriteType {
        Enemy,
        Player,
        Missile,
        Background
    };

    class SpriteElement {
    public:
        sf::Sprite sprite;
        int id;
    };

    class Client {
    public:
        Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port);
        ~Client();
        void send(const std::string& message);
        void start_receive();
        int main_loop();
        std::string createPacket(Network::PacketType type);

        void sendExitPacket() {
            send(createPacket(Network::PacketType::DISCONNECTED));
        }

    private:
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred);
        void run_receive();
        void createSprite();
        void loadTextures();
        void drawSprites(sf::RenderWindow& window);
        void updateSpritePosition();
        void parseMessage(const std::string& messageRecieved, std::size_t bytes_transferred);
        void destroySprite();
        void processEvents(sf::RenderWindow& window);

        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint server_endpoint_;
        std::array<char, MAX_LENGTH> recv_buffer_;
        std::thread receive_thread_;
        boost::asio::io_context& io_context_;
        std::vector<SpriteElement> sprites_;
        std::unordered_map<SpriteType, sf::Texture> textures_;
        std::string action;
        std::size_t server_id;
        float new_x = 0.0, new_y = 0.0;
    };
}
