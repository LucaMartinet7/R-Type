#include <gtest/gtest.h>
#include "Game.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "Entity/Player.hpp"
#include "Entity/Bullet.hpp"
#include "Entity/Enemy.hpp"

// Test Fixture for the Game class
class GameTest : public ::testing::Test {
protected:
    Game game;

    void SetUp() override {
        // Set up initial state
    }

    void TearDown() override {
        // Clean up after test
    }
};

// Test: Components are registered successfully
TEST_F(GameTest, ComponentRegistration) {
    EXPECT_NO_THROW({
        game.registry.register_component<Position>();
        game.registry.register_component<Velocity>();
    });
}

// Test: Creating a Player entity
TEST_F(GameTest, CreatePlayerEntity) {
    Player player(game.registry, 50.0f, 50.0f);
    auto position = game.registry.get_components<Position>()[player.getEntity()];
    ASSERT_NE(position, nullptr);
    EXPECT_FLOAT_EQ(position->x, 50.0f);
    EXPECT_FLOAT_EQ(position->y, 50.0f);
}

// Test: Creating an Enemy entity
TEST_F(GameTest, CreateEnemyEntity) {
    Enemy enemy(game.registry, 375.0f, 275.0f);
    auto position = game.registry.get_components<Position>()[enemy.getEntity()];
    ASSERT_NE(position, nullptr);
    EXPECT_FLOAT_EQ(position->x, 375.0f);
    EXPECT_FLOAT_EQ(position->y, 275.0f);
}

// Test: Shooting creates a Bullet entity
TEST_F(GameTest, ShootCreatesBullet) {
    game.shoot();
    auto& bullets = game.registry.get_components<Projectile>();
    bool bulletCreated = false;

    for (const auto& bullet : bullets) {
        if (bullet) {
            bulletCreated = true;
            break;
        }
    }

    EXPECT_TRUE(bulletCreated);
}

// Test: Collisions are detected correctly
TEST_F(GameTest, CollisionDetection) {
    Player player(game.registry, 50.0f, 50.0f);
    Enemy enemy(game.registry, 50.0f, 50.0f);

    auto collisions = collision_system(
        game.registry,
        game.registry.get_components<Position>(),
        game.registry.get_components<Drawable>(),
        game.registry.get_components<Collidable>(),
        game.registry.get_components<Controllable>(),
        game.registry.get_components<Projectile>(),
        true
    );

    EXPECT_FALSE(collisions.empty());
}

// Test: Game starts when start button is clicked
TEST_F(GameTest, StartButtonClickStartsGame) {
    sf::Vector2i fakeMousePos(100, 100);
    game.menu.setStartButtonBounds(sf::IntRect(50, 50, 200, 100)); // Mock the button bounds
    EXPECT_FALSE(game.gameStarted);
    game.handlePlayerInput(sf::Mouse::Left, true);
    EXPECT_TRUE(game.gameStarted);
}

// Test: No players remaining ends the game
TEST_F(GameTest, GameOverNoPlayers) {
    game.update(); // Mock update call with no controllable entities
    EXPECT_FALSE(game.hasPlayers);
    EXPECT_FALSE(game.gameStarted);
    EXPECT_TRUE(game.menu.isGameOver());
}

