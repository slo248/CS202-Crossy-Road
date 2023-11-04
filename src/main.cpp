#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML White Window");

    sf::Sprite button;
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("/asset/DiscardButton.png")) {
    }

    button.setTexture(buttonTexture);
    button.setPosition(100.0f, 100.0f);

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.draw(button);
        window.display();
    }

    return 0;
}
