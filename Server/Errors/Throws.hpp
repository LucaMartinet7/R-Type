/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Throws
*/

#pragma once

#include <exception>
#include <string>

/*!
 * @brief Macro to define custom exceptions.
 * @param name The name of the exception.
 */
#define NEW_EXCEPTION(name)                                                        \
    class name : public RType::NtsException                                        \
    {                                                                              \
    public:                                                                        \
        name(std::string const &message, std::string const &type = #name) noexcept \
            : RType::NtsException(message, type) {}                                \
    };

namespace RType
{
    /*!
     * @class NtsException
     * @brief Base class for custom exceptions.
     * @details This class stores a message and a type for identifying specific exceptions.
     */
    class NtsException : public std::exception
    {
    public:
        /*!
         * @brief Constructs a new NtsException object.
         * @param message The error message.
         * @param type The type of the exception.
         */
        NtsException(std::string const &message, std::string const &type = "Unknown") noexcept
        {
            _message = message;
            _type = type;
        }

        /*!
         * @brief Retrieves the type of the exception.
         * @return A string reference to the exception type.
         */
        std::string const &getType() const { return _type; }

        /*!
         * @brief Retrieves the error message.
         * @return A C-string of the error message.
         */
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message; /*!< The error message. */
        std::string _type; /*!< The type of the exception. */
    };

    // Parse exceptions
    NEW_EXCEPTION(InvalidPortException)

    // General exceptions
    NEW_EXCEPTION(StandardException)
    NEW_EXCEPTION(UnknownException)
    NEW_EXCEPTION(PermissionDeniedException)
}
