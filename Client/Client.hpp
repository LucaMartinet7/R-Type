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

        void sendExitPacket() {
            std::string exit_message = "DISCONNECTED";
            send(exit_message);
        }

    private:
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred);
        void run_receive();   
        void createSprite(const std::string& type, int server_id, float x, float y);
        void loadTextures();
        void drawSprites(sf::RenderWindow& window);
        void updateSpritePosition(size_t server_id, float x, float y);
        void parseMessage(const std::string& input);
        void destroySprite(size_t index);
        void processEvents(sf::RenderWindow& window);
        int main_loop();

        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint server_endpoint_;
        std::array<char, MAX_LENGTH> recv_buffer_;
        std::thread receive_thread_;
        boost::asio::io_context& io_context_;
        std::vector<SpriteElement> sprites_;
        std::unordered_map<SpriteType, sf::Texture> textures_;
    };
}
