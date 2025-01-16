/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include "../Server/Network/Packet.hpp"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <csignal>
#include <unordered_map>

#define MAX_LENGTH 1024

namespace RType {
    enum class SpriteType {
        Enemy,
        Boss,
        Player,
        Bullet,
        Background,
        Lobby_background,
        Start_button
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
        void parseMessage(std::string packet_data);
        void destroySprite();
        void processEvents(sf::RenderWindow& window);
        void initLobbySprites(sf::RenderWindow& window);
        std::string createMousePacket(Network::PacketType type, int x = 0, int y = 0);

        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint server_endpoint_;
        std::array<char, MAX_LENGTH> recv_buffer_;
        std::string received_data;
        std::mutex mutex_;
        std::thread receive_thread_;
        boost::asio::io_context& io_context_;
        std::vector<SpriteElement> sprites_;
        std::unordered_map<SpriteType, sf::Texture> textures_;
        std::size_t action;
        std::size_t server_id;
        float new_x = 0.0, new_y = 0.0;
    };
}
