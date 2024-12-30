/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** main
*/

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "Server.hpp"
#include "Errors/Throws.hpp"
#include "Network/Packet.hpp"
#include "Network/ThreadSafeQueue.hpp"
#include "Network/PacketHandler.hpp"

/*!
 * @brief Parses the command-line arguments to retrieve the port number.
 * @param ac The argument count.
 * @param av The argument vector.
 * @return The parsed port number.
 * @throws RType::InvalidPortException If the arguments are invalid or the port is invalid.
 */
short parsePort(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <port>" << std::endl;
        throw RType::InvalidPortException("Invalid number of arguments");
    }
    try {
        return std::stoi(av[1]);
    } catch (const std::exception& e) {
        throw RType::InvalidPortException("Invalid port number");
    }
}

/*!
 * @brief Runs the server on the specified port.
 * @param port The UDP port number to listen on.
 * @throws RType::PermissionDeniedException If the server lacks permissions to bind to the port.
 */
void runServer(short port)
{
    try {
        boost::asio::io_context io_context;
        ThreadSafeQueue<Network::Packet> packetQueue;
        Network::PacketHandler packetHandler(packetQueue);
        packetHandler.start();

        RType::Server server(io_context, port, packetQueue);

        std::cout << "Server started" << std::endl;
        std::cout << "Listening on UDP port " << port << std::endl;

        io_context.run();

        packetHandler.stop();
    } catch (const boost::system::system_error& e) {
        if (e.code() == boost::asio::error::access_denied) {
            throw RType::PermissionDeniedException("Permission denied");
        } else {
            throw;
        }
    }
}

/*!
 * @brief The main entry point for the R-Type server.
 * @param ac The argument count.
 * @param av The argument vector.
 * @return 0 on success, -1 on failure.
 */
int main(int ac, char **av)
{
    try {
        short port = parsePort(ac, av);
        runServer(port);
    } catch (const RType::NtsException& e) {
        std::cerr << "Exception: " << e.what() << " (Type: " << e.getType() << ")" << std::endl;
    } catch (const std::exception& e) {
        throw RType::StandardException(e.what());
    } catch (...) {
        throw RType::UnknownException("Unknown exception occurred");
    }
    return 0;
}
