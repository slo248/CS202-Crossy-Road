#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include "Button.hpp"
#include "Textbox.hpp"

int main() {
    FontHolder fonts;
    fonts.load(Fonts::Main, "asset/Sansation.ttf");
    TextureHolder textures;
    textures.load(Textures::TextBackground, "asset/ButtonNormal.png");
    GUI::Textbox textbox("Textbox", fonts, textures, 16);
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML White Window");
    sf::Sprite button;
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("asset/ButtonNormal.png")) {
    }

    button.setTexture(buttonTexture);
    button.setPosition(100.0f, 100.0f);

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        window.draw(textbox);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            textbox.handleEvent(event);
        }
        window.display();
    }

    return 0;
}
