/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** ThreadSafeQueue
*/

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

/*!
 * @class ThreadSafeQueue
 * @brief A thread-safe queue implementation for handling concurrent access.
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class ThreadSafeQueue {
public:
    /*!
     * @brief Default constructor.
     */
    ThreadSafeQueue() = default;

    /*!
     * @brief Default destructor.
     */
    ~ThreadSafeQueue() = default;

    // Prevent copying
    /*!
     * @brief Copy constructor is deleted to prevent copying.
     */
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;

    /*!
     * @brief Copy assignment operator is deleted to prevent copying.
     */
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    /*!
     * @brief Adds an item to the queue.
     * @param value The item to add.
     */
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(std::move(value));
        }
        m_cond_var.notify_one();
    }

    /*!
     * @brief Retrieves and removes an item from the queue.
     * @return The item from the front of the queue.
     * @details This call blocks if the queue is empty.
     */
    T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond_var.wait(lock, [this] { return !m_queue.empty(); });
        T value = std::move(m_queue.front());
        m_queue.pop();
        return value;
    }

    /*!
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    mutable std::mutex m_mutex; /*!< Mutex for thread safety. */
    std::condition_variable m_cond_var; /*!< Condition variable for synchronization. */
    std::queue<T> m_queue; /*!< The underlying queue. */
};
