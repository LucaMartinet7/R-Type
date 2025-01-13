/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#include "Client.hpp"

#include <string>

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
    io_context_.stop();
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
        mutex_.lock();
        received_data.assign(recv_buffer_.data(), bytes_transferred);

        // uint8_t packet_type = static_cast<uint8_t>(received_data[0]);

        // std::string packet_data = received_data.substr(2);
        // std::cout << "[DEBUG] Received Packet Type: " << static_cast<int>(packet_type) << std::endl;
        // std::cout << "[DEBUG] Received Packet Data: " << packet_data << std::endl;
        parseMessage(received_data);
        start_receive();
    } else {
        std::cerr << "[DEBUG] Error receiving: " << error.message() << std::endl;
    }
}

void RType::Client::handle_send(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "[DEBUG] Message sent." << std::endl;
    } else {
        std::cerr << "[DEBUG] Error sending: " << error.message() << std::endl;
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

    if (action == 1) { //change by used ID in server to create different types of sprites to be displayed
        spriteType = SpriteType::Enemy;
    } else if (action == 2) {
        spriteType = SpriteType::Player;
    } else if (action == 3) {
        spriteType = SpriteType::Missile;
    } else if (action == 4) {
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

void RType::Client::parseMessage(std::string packet_data) //parse the packet send by server and stores the data in the right variables in Client class
{
    std::stringstream ss(packet_data);
    std::string segment;
    std::vector<std::string> elements;

    while (std::getline(ss, segment, ';'))
        elements.push_back(segment);

    if (elements.size() != 4) {
        std::cerr << "[ERROR] Invalid packet format: " << packet_data << std::endl;
        return;
    }

    try {
        action = std::stoul(elements[0]); //stoul converts string to unsigned long
        server_id = std::stoul(elements[1]);
        new_x = std::stof(elements[2]);
        new_y = std::stof(elements[3]);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Failed to parse packet data: " << e.what() << std::endl;
    }
}

int RType::Client::main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Client");
    loadTextures();
    send(createPacket(Network::PacketType::REQCONNECT));

    while (window.isOpen()) { //received data is modified in handle receive function and parsed here
        // parseMessage(received_data);
        processEvents(window);
        createSprite();
        destroySprite();
        updateSpritePosition();
        mutex_.unlock();

        window.clear();
        drawSprites(window);
        window.display();
    }
    sendExitPacket();
    return 0;
}

std::string RType::Client::createPacket(Network::PacketType type)
{
    Network::Packet packet;
    packet.type = type;
    std::string packet_str;
    packet_str.push_back(static_cast<uint8_t>(type));
    return packet_str;
}

std::string deserializePacket(const std::string& packet_str)
{
    Network::Packet packet;
    packet.type = static_cast<Network::PacketType>(packet_str[0]);
    return packet_str;
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
                std::cout << "[DEBUG] Sending Right: " << std::endl;
                send(createPacket(Network::PacketType::PLAYER_RIGHT));
            }
            if (event.key.code == sf::Keyboard::Left) {
                std::cout << "[DEBUG] Sending Left: " << std::endl;
                send(createPacket(Network::PacketType::PLAYER_LEFT));
            }
            if (event.key.code == sf::Keyboard::Up) {
                std::cout << "[DEBUG] Sending Up: " << std::endl;
                send(createPacket(Network::PacketType::PLAYER_UP));
            }
            if (event.key.code == sf::Keyboard::Down) {
                std::cout << "[DEBUG] Sending Down: " << std::endl;
                send(createPacket(Network::PacketType::PLAYER_DOWN));
            }
            if (event.key.code == sf::Keyboard::Q) {
                sendExitPacket();
                window.close();
            }
            if (event.key.code == sf::Keyboard::M) {
                std::cout << "[DEBUG] Sending M: " << std::endl;
                send(createPacket(Network::PacketType::OPEN_MENU));
            }
        }
    }
}

