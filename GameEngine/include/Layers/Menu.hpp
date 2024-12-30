#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

/*!
 * @class Menu
 * @brief Represents the game menu.
 * @details Handles rendering of the start menu, game-over screen, and user interaction.
 */
class Menu {
public:
    /*!
     * @brief Constructs a new Menu object.
     * @details Initializes the menu UI components such as the background, start button, and text.
     * @throws std::runtime_error If the font fails to load.
     */
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

    /*!
     * @brief Renders the menu to the given window.
     * @param window The SFML render window to draw the menu on.
     */
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

    /*!
     * @brief Checks if the start button is clicked.
     * @param mousePos The position of the mouse click.
     * @return True if the start button is clicked, false otherwise.
     */
    bool isStartButtonClicked(const sf::Vector2i& mousePos) const {
        return startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    /*!
     * @brief Sets the game-over state.
     * @param state The new game-over state.
     */
    void setGameOver(bool state) {
        gameOver = state;
    }

private:
    sf::Font font; /*!< The font used for menu text. */
    sf::Text title; /*!< The title text displayed on the menu. */
    sf::Text startButtonText; /*!< The text displayed on the start button. */
    sf::Text gameOverText; /*!< The text displayed during the game-over screen. */
    sf::RectangleShape startButton; /*!< The start button. */
    sf::RectangleShape background; /*!< The menu background. */
    bool gameOver; /*!< Whether the game is over. */
};

#endif // MENU_HPP
