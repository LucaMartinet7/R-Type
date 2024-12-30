/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** main
*/

#include "Client.hpp"

/*!
 * @brief Global pointer to the R-Type Client object.
 * @details Used to send an exit packet when the program receives a termination signal.
 */
RType::Client* global_client = nullptr;

/*!
 * @brief Signal handler for termination signals.
 * @param signum The signal number received.
 * @details This function sends a disconnect packet to the server and exits the program gracefully.
 */
void signalHandler(int signum) {
    if (global_client) {
        global_client->sendExitPacket();
    }
    std::exit(signum);
}

/*!
 * @brief Main entry point of the R-Type Client program.
 * @param ac The argument count.
 * @param av The argument vector.
 * @return Returns 0 on success, or 1 on failure.
 * @details Initializes the R-Type client, sets up a signal handler for graceful shutdown,
 * and starts the main execution loop.
 * 
 * Usage:
 * @code
 * ./program <host> <server-port> <client-port>
 * @endcode
 */
int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: " << av[0] << " <host> <server-port> <client-port>" << std::endl;
        return 1;
    }

    std::string host = av[1];
    short server_port = std::stoi(av[2]);
    short client_port = std::stoi(av[3]);

    try {
        boost::asio::io_context io_context;
        RType::Client client(io_context, host, server_port, client_port);
        global_client = &client;

        /*!
         * @brief Sets up the SIGINT signal handler for graceful termination.
         */
        std::signal(SIGINT, signalHandler);

        // Uncomment below lines to enable manual message sending from stdin
        // std::string message;
        // while (std::getline(std::cin, message)) {
        //     client.send(message);
        // }

        /*!
         * @brief Starts the main client execution loop.
         */
        client.run();
        
    } catch (const std::exception& e) {
        /*!
         * @brief Handles any exceptions that occur during execution.
         * @param e The exception caught.
         */
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
