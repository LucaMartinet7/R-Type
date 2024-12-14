#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Game");
    Game game;

    game.initLayer();

    while (window.isOpen()) {
        int event = game.manageEvent(window);
        if (event == sf::Event::Closed) {
            window.close();
        }

        window.clear();
        game.displayLayer(window);
        window.display();
    }

    game.deleteElements();

    return 0;
}
