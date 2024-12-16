#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/asio.hpp>
#include "Client.hpp"

// Mock classes to simulate Boost.Asio and SFML behaviors
class MockSocket : public boost::asio::ip::udp::socket {
public:
    MockSocket(boost::asio::io_context& io_context)
        : boost::asio::ip::udp::socket(io_context) {}

    MOCK_METHOD(void, async_send_to, (const boost::asio::const_buffer&, const boost::asio::ip::udp::endpoint&,
                                      boost::asio::ip::udp::resolver::iterator), ());
    MOCK_METHOD(void, async_receive_from, (boost::asio::mutable_buffer&, boost::asio::ip::udp::endpoint&,
                                           boost::asio::ip::udp::resolver::iterator), ());
};

// Test Fixture
class ClientTest : public ::testing::Test {
protected:
    boost::asio::io_context io_context;
    RType::Client* client;
    MockSocket* mock_socket;

    void SetUp() override {
        // Create a mock socket and initialize the client
        mock_socket = new MockSocket(io_context);
        client = new RType::Client(io_context, "127.0.0.1", 8080, 7070);
    }

    void TearDown() override {
        delete client;
        delete mock_socket;
    }
};

// Test: Client initializes successfully
TEST_F(ClientTest, Initialization) {
    EXPECT_NO_THROW({
        RType::Client client(io_context, "127.0.0.1", 8080, 7070);
    });
}

// Test: Client sends a message
TEST_F(ClientTest, SendMessage) {
    EXPECT_NO_THROW({
        client->send("TEST_MESSAGE");
    });
}

// Test: Process events with key presses
TEST_F(ClientTest, ProcessEvents) {
    // Simulate a key press for moving the player
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Right;

    client->processEvents(); // Should process the event without error
}

// Test: Client handles player rendering
TEST_F(ClientTest, RenderPlayer) {
    // Simulate rendering logic
    EXPECT_NO_THROW({
        client->render();
    });
}

// Test: Signal handler triggers proper cleanup
TEST(SignalHandlerTest, HandleSignal) {
    RType::Client* test_client = nullptr;
    EXPECT_NO_THROW({
        boost::asio::io_context io_context;
        test_client = new RType::Client(io_context, "127.0.0.1", 8080, 7070);
        signalHandler(SIGINT); // Trigger signal handler
        delete test_client;
    });
}
