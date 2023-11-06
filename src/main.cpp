#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.hpp"
#include "Dialog.hpp"
#include "Label.hpp"
#include "Textbox.hpp"

int main() {
    FontHolder fonts;
    TextureHolder textures;
    fonts.load(Fonts::Main, "asset/Sansation.ttf");

    textures.load(Textures::TextBackground, "asset/ButtonSelected.png");
    Textbox textbox("Textbox", fonts, textures, 16);
    textbox.setPosition(500, 500);

    textures.load(Textures::DialogBackground, "asset/ButtonSelected.png");
    Dialog dialog("Dialog", fonts, textures);
    dialog.setPosition(300, 300);

    textures.load(Textures::ButtonNormal, "asset/ButtonNormal.png");
    textures.load(Textures::ButtonSelected, "asset/ButtonSelected.png");
    textures.load(Textures::ButtonPressed, "asset/ButtonPressed.png");
    Button button(fonts, textures);
    button.setText("Button");
    button.setPosition(100, 100);

    textures.load(Textures::LabelBackground, "asset/ButtonSelected.png");
    Label label("Label", fonts, textures);
    label.setPosition(200, 200);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML White Window");

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        window.draw(textbox);
        window.draw(button);
        window.draw(label);
        window.draw(dialog);

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
