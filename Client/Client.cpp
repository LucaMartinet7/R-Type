/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#include <string> 
#include "../Server/Network/Packet.hpp"
#include "Client.hpp"

using boost::asio::ip::udp;

RType::Client::Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port)
    : socket_(io_context, udp::endpoint(udp::v4(), client_port)), io_context_(io_context)
{
    udp::resolver resolver(io_context);
    udp::resolver::query query(udp::v4(), host, std::to_string(server_port));
    server_endpoint_ = *resolver.resolve(query).begin();
    std::cout << "Connected to " << host << ":" << server_port << " from client port " << client_port << std::endl;

    start_receive();
    receive_thread_ = std::thread(&Client::run_receive, this);
}

RType::Client::~Client()
{
    socket_.close();
    if (receive_thread_.joinable()) {
        receive_thread_.join();
    }
}

void RType::Client::send(const std::string& message)
{
    socket_.async_send_to(
        boost::asio::buffer(message), server_endpoint_,
        boost::bind(&Client::handle_send, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RType::Client::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), server_endpoint_,
        boost::bind(&RType::Client::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RType::Client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_transferred) << std::endl;
        start_receive();
    } else {
        std::cerr << "Error receiving: " << error.message() << std::endl;
    }
}

void RType::Client::handle_send(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Message sent." << std::endl;
    } else {
        std::cerr << "Error sending: " << error.message() << std::endl;
    }
}

void RType::Client::run_receive()
{
    io_context_.run();
}

void RType::Client::createSprite()
{
    SpriteElement spriteElement;
    SpriteType spriteType;

    if (action == "Enemy") {
        spriteType = SpriteType::Enemy;
    } else if (action == "Player") {
        spriteType = SpriteType::Player;
    } else if (action == "Missile") {
        spriteType = SpriteType::Missile;
    } else if (action == "Background") {
        spriteType = SpriteType::Background;
    } else {
        return;
    }

    spriteElement.sprite.setTexture(textures_[spriteType]);
    spriteElement.sprite.setPosition(new_x, new_y);
    spriteElement.id = server_id;
    sprites_.push_back(spriteElement);
}

void RType::Client::destroySprite()
{
    for (auto it = sprites_.begin(); it != sprites_.end(); ++it) {
        if (server_id == it->id) {
            sprites_.erase(it);
            break;
        }
    }
}

void RType::Client::loadTextures() //make sure to have the right textures in the right folder
{
    textures_[RType::SpriteType::Enemy].loadFromFile("enemy.png");
    textures_[RType::SpriteType::Player].loadFromFile("player.png");
    textures_[RType::SpriteType::Missile].loadFromFile("missile.png");
    textures_[RType::SpriteType::Background].loadFromFile("background.png");
}

void RType::Client::drawSprites(sf::RenderWindow& window)
{
    for (auto& spriteElement : sprites_) {
        window.draw(spriteElement.sprite);
    }
}

void RType::Client::updateSpritePosition()
{
    for (auto& spriteElement : sprites_) {
        if (server_id == spriteElement.id) {
            spriteElement.sprite.setPosition(new_x, new_y);
            break;
        }
    }
}

void RType::Client::parseMessage(const std::string& input)
{
    
    size_t move = input.find("PLAYER_MOVED");
    if (move == std::string::npos) {
        return;
    }

    size_t delimiterPos = input.find(';');
    if (delimiterPos != std::string::npos) {
        action = input.substr(0, delimiterPos);
    }
}

int RType::Client::main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Client");
    loadTextures();

    while (window.isOpen()) {
        processEvents(window);

        std::string input(recv_buffer_.data());
        parseMessage(input);
        createSprite();
        destroySprite();
        updateSpritePosition();

        window.clear();
        drawSprites(window);
        window.display();
    }

    return 0;
}

void RType::Client::processEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
                send(std::to_string(static_cast<std::uint8_t>(Network::PacketType::PLAYER_RIGHT)));
            }
            if (event.key.code == sf::Keyboard::Left) {
                send(std::to_string(static_cast<std::uint8_t>(Network::PacketType::PLAYER_LEFT)));
            }
            if (event.key.code == sf::Keyboard::Up) {
                send(std::to_string(static_cast<std::uint8_t>(Network::PacketType::PLAYER_UP)));
            }
            if (event.key.code == sf::Keyboard::Down) {
                send(std::to_string(static_cast<std::uint8_t>(Network::PacketType::PLAYER_DOWN)));
            }
            if (event.key.code == sf::Keyboard::Q) {
                sendExitPacket();
                window.close();
            }
            if (event.key.code == sf::Keyboard::M) {
                send(std::to_string(static_cast<std::uint8_t>(Network::PacketType::OPEN_MENU)));
            }
        }
    }
}

