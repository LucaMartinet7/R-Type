/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#include "Server.hpp"

using boost::asio::ip::udp;

/**
 * @brief Constructs a new Server object.
 *
 * This constructor initializes the UDP socket and starts the asynchronous
 * receive operation to handle incoming data.
 *
 * @param io_context The io_context object used for asynchronous operations.
 * @param port The port number on which the server will listen for incoming UDP packets.
 */
RType::Server::Server(boost::asio::io_context &io_context, short port, ThreadSafeQueue<Network::Packet> &packetQueue, GameState &game)
: socket_(io_context, udp::endpoint(udp::v4(), port)), m_packetQueue(packetQueue), _nbClients(0), m_game(game)
{
    start_receive();
}


RType::Server::~Server()
{
    socket_.close();
}

//SEND MESSAGES

void RType::Server::send_to_client(const std::string& message, const udp::endpoint& client_endpoint)
{
    socket_.async_send_to(
        boost::asio::buffer(message), client_endpoint,
        [](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::cout << "[DEBUG] Message sent to client." << std::endl;
            } else {
                std::cerr << "[DEBUG] Error sending to client: " << error.message() << std::endl;
            }
        });
}

void RType::Server::Broadcast(const std::string& message)
{
    for (const auto& client : clients_) {
        send_to_client(message, client.second.getEndpoint());
    }
}

/**
 * @brief Starts an asynchronous receive operation.
 *
 * This function initiates an asynchronous receive operation to receive data
 * from a remote endpoint. When data is received, the provided handler function
 * is called to process the received data.
 */
void RType::Server::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&RType::Server::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * @brief Handles the completion of an asynchronous receive operation.
 *
 * This function is called when data is received from a remote endpoint. It processes
 * the received data, optionally sends a response back to the client, and restarts
 * the asynchronous receive operation to handle the next incoming message.
 *
 * @param error The error code indicating the result of the receive operation.
 * @param bytes_transferred The number of bytes received.
 */

void RType::Server::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string received_data(recv_buffer_.data(), bytes_transferred);
        std::cout << "[DEBUG] Received: " << static_cast<int>(received_data[0]) << std::endl;

        Network::Packet packet;
        packet.type = deserializePacket(received_data).type;
        switch (packet.type) {
            case Network::PacketType::REQCONNECT:
                packet.data = reqConnectData(remote_endpoint_);
                break;
            case Network::PacketType::DISCONNECTED:
                packet.data = disconnectData(remote_endpoint_);
                break;
            default:
                handle_game_packet(packet, remote_endpoint_);
                break;
        }
        m_packetQueue.push(packet);
        start_receive();
    }
}

void RType::Server::handle_game_packet(const Network::Packet& packet, const udp::endpoint& client_endpoint)
{
    switch (packet.type) {
        case Network::PacketType::PLAYER_DOWN:
            break;
        case Network::PacketType::PLAYER_UP:
            break;
        case Network::PacketType::PLAYER_LEFT:
            break;
        case Network::PacketType::PLAYER_RIGHT:
            break;
        case Network::PacketType::OPEN_MENU:
            break;
        default:
            std::cerr << "[DEBUG] Unknown packet type." << std::endl;
            break;
    }
}

Network::Packet RType::Server::deserializePacket(const std::string& packet_str)
{
    Network::Packet packet;
    packet.type = static_cast<Network::PacketType>(packet_str[0]);
    return packet;
}

std::string RType::Server::createPacket(const Network::PacketType& type, const std::string& data)
{
    std::string packet_str;

    packet_str.push_back(static_cast<uint8_t>(type));
    packet_str.push_back(static_cast<uint8_t>(';'));
    if (!data.empty())
        packet_str.append(data);
    else
        packet_str.push_back(static_cast<uint8_t>('0'));
    return packet_str;
}

//COMMANDS

uint32_t RType::Server::createClient(boost::asio::ip::udp::endpoint& client_endpoint)
{
    uint32_t nb = this->_nbClients;

    for (const auto& client : clients_) {
        if (client.second.getEndpoint() == client_endpoint)
            return client.first;
    }
    ClientRegister newClient(nb, client_endpoint);
    clients_.insert(std::make_pair(nb, newClient));
    this->_nbClients++;
    return nb;
}

Network::ReqConnect RType::Server::reqConnectData(boost::asio::ip::udp::endpoint& client_endpoint)
{
    Network::ReqConnect data;
    size_t idClient;
    idClient = createClient(client_endpoint);
    data.id = idClient;
    send_to_client(createPacket(Network::PacketType::REQCONNECT, ""), client_endpoint);
    return data;
}

Network::DisconnectData RType::Server::disconnectData(boost::asio::ip::udp::endpoint& client_endpoint)
{
    Network::DisconnectData data;
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (it->second.getEndpoint() == client_endpoint) {
            data.id = it->second.getId();
            std::cout << "[DEBUG] Client " << data.id << " disconnected." << std::endl;
            clients_.erase(it);
            return data;
        }
    }
    data.id = -1;
    std::cerr << "Client not found." << std::endl;
    send_to_client(createPacket(Network::PacketType::DISCONNECTED, ""), client_endpoint);
    return data;
}

void RType::Server::PacketFactory() //need to do the send for entities and bullets
{
    for (int playerId = 0; playerId < m_game.getPlayerCount(); ++playerId) { 
        try {
            auto [x, y] = m_game.getPlayerPosition(playerId);
            std::string data = std::to_string(playerId) + ";" + std::to_string(x) + ";" + std::to_string(y);
            Broadcast(createPacket(Network::PacketType::CHANGE, data));
        } catch (const std::out_of_range& e) {
            std::cerr << "[ERROR] Invalid player ID: " << playerId << " - " << e.what() << std::endl;
        }
    }

    for (int enemyId = 0; enemyId < m_game.getEnemiesCount(); ++enemyId) { 
        try {
            auto [x, y] = m_game.getEnemyPosition(enemyId);
            std::string data = "Enemy;" + std::to_string(enemyId) + ";" + std::to_string(x) + ";" + std::to_string(y);
            Broadcast(createPacket(Network::PacketType::CHANGE, data));
        } catch (const std::out_of_range& e) {
            std::cerr << "[ERROR] Invalid enemy ID: " << enemyId << " - " << e.what() << std::endl;
        }
    }

    for (int bulletId = 0; bulletId < m_game.getBulletsCount(); ++bulletId) { 
        try {
            auto [x, y] = m_game.getBulletPosition(bulletId);
            std::string data = "Bullet;" + std::to_string(bulletId) + ";" + std::to_string(x) + ";" + std::to_string(y);
            Broadcast(createPacket(Network::PacketType::CHANGE, data));
        } catch (const std::out_of_range& e) {
            std::cerr << "[ERROR] Invalid bullet ID: " << bulletId << " - " << e.what() << std::endl;
        }
    }
}
