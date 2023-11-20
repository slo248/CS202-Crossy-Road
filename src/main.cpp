#include <SFML/Graphics.hpp>

#include "CreditState.hpp"
#include "LoseState.hpp"
#include "State.hpp"
#include "StateStack.hpp"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(
        sf::VideoMode(1152, 960), "Pro Game", sf::Style::Default
    );
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    TextureHolder textures;
    textures.load(
        Textures::CreditBackground, "asset/textures/CreditBackground.png"
    );
    textures.load(Textures::BackButton, "asset/textures/ButtonBack.png");
    textures.load(
        Textures::MainBackground, "asset/textures/MainBackground.png"
    );
    textures.load(Textures::DefeatDialog, "asset/textures/DefeatDialog.png");

    FontHolder fonts;
    fonts.load(Fonts::Main, "asset/Sansation.ttf");

    State::Context context(window, textures, fonts);
    StateStack stack(context);
    CreditState creditState(stack, context);
    LoseState loseState(stack, context);
    stack.registerState<CreditState>(States::Credit);
    stack.registerState<LoseState>(States::Lose);
    stack.pushState(States::Lose);
    stack.pushState(States::Credit);

    while (stack.mContext.window->isOpen()) {
        stack.mContext.window->clear(sf::Color::White);
        sf::Event event;
        stack.draw();
        while (stack.mContext.window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stack.mContext.window->close();
            }
            stack.handleEvent(event);
        }
        stack.mContext.window->display();
    }

    return 0;
}
