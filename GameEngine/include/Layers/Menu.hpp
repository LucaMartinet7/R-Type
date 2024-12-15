#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu() : gameOver(false) {
        if (!font.loadFromFile("../assets/font.otf")) {
            throw std::runtime_error("Failed to load font");
        }

        // Set up the background
        background.setSize(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(50, 50, 50));

        // Set up the start button
        startButton.setSize(sf::Vector2f(200, 100));
        startButton.setFillColor(sf::Color::Green);
        startButton.setPosition(300, 250);
        startButton.setOutlineThickness(5);
        startButton.setOutlineColor(sf::Color::White);

        // Set up the title text
        title.setFont(font);
        title.setString("Click to Start");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::White);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
        title.setPosition(400, 150);

        // Set up the start button text
        startButtonText.setFont(font);
        startButtonText.setString("Start");
        startButtonText.setCharacterSize(30);
        startButtonText.setFillColor(sf::Color::White);
        startButtonText.setPosition(370, 280);

        // Set up the game over text
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f, gameOverBounds.top + gameOverBounds.height / 2.0f);
        gameOverText.setPosition(400, 300); // Centered in the middle of the screen
    }

    void render(sf::RenderWindow& window) {
        window.draw(background);
        if (gameOver) {
            window.draw(gameOverText);
        } else {
            window.draw(title);
            window.draw(startButton);
            window.draw(startButtonText);
        }
    }

    bool isStartButtonClicked(const sf::Vector2i& mousePos) const {
        return startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void setGameOver(bool state) {
        gameOver = state;
    }

private:
    sf::Font font;
    sf::Text title;
    sf::Text startButtonText;
    sf::Text gameOverText;
    sf::RectangleShape startButton;
    sf::RectangleShape background;
    bool gameOver;
};

#endif // MENU_HPP
