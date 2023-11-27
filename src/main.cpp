#include <SFML/Graphics.hpp>

#include "CreditState.hpp"
#include "LoseState.hpp"
#include "SettingState.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "WinState.hpp"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(
        sf::VideoMode(1152, 960), "Pro Game", sf::Style::Default
    );
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    FontHolder fonts;
    TextureHolder textures;
    textures.loadTextureFromFile();
    fonts.loadFontFromFile();

    Player player;
    State::Context context(window, textures, fonts, player);
    StateStack stack(context);
    CreditState creditState(stack, context);
    WinState winState(stack, context);
    LoseState loseState(stack, context);
    SettingState settingState(stack, context);

    stack.registerState<SettingState>(States::Setting);
    stack.registerState<CreditState>(States::Credit);
    stack.registerState<WinState>(States::Win);
    stack.registerState<LoseState>(States::Lose);

    stack.pushState(States::Credit);
    stack.pushState(States::Setting);
    //stack.pushState(States::Win);
    //stack.pushState(States::Lose);

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
