/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** ClientRegister
*/

#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::udp;

/*!
 * @class ClientRegister
 * @brief Represents a client registration record.
 * @details Stores the client's unique ID and endpoint information for communication.
 */
class ClientRegister {
    public:
        /*!
         * @brief Constructs a new ClientRegister object.
         * @param id The unique identifier for the client.
         * @param endpoint The endpoint associated with the client.
         */
        ClientRegister(size_t id, udp::endpoint endpoint): _id(id), _endpoint(endpoint) {}

        /*!
         * @brief Retrieves the unique ID of the client.
         * @return The client's unique identifier.
         */
        size_t getId() const { return _id; };

        /*!
         * @brief Retrieves the endpoint associated with the client.
         * @return The client's UDP endpoint.
         */
        udp::endpoint getEndpoint() const { return _endpoint; };

    private:
        size_t _id; /*!< Unique identifier for the client. */
        udp::endpoint _endpoint; /*!< UDP endpoint associated with the client. */
};
