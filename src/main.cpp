#include <SFML/Graphics.hpp>

#include "ChooseModeState.hpp"
#include "CreditState.hpp"
#include "LevelState.hpp"
#include "LoseState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "RankingState.hpp"
#include "SavedState.hpp"
#include "SettingState.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "WinState.hpp"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(
        sf::VideoMode(896, 640), "Pro Game", sf::Style::Default
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
    PauseState pauseState(stack, context);
    MenuState menuState(stack, context);
    RankingState rankingState(stack, context);
    ChooseModeState chooseModeState(stack, context);

    stack.registerState<SettingState>(States::Setting);
    stack.registerState<CreditState>(States::Credit);
    stack.registerState<WinState>(States::Win);
    stack.registerState<LoseState>(States::Lose);
    stack.registerState<PauseState>(States::Pause);
    stack.registerState<MenuState>(States::Menu);
    stack.registerState<RankingState>(States::Ranking);
    stack.registerState<LevelState>(States::Level);
    stack.registerState<SavedState>(States::Saved);
    stack.registerState<ChooseModeState>(States::ChooseMode);

    stack.pushState(States::Credit);
    stack.pushState(States::Setting);
    // stack.pushState(States::Win);
    // stack.pushState(States::Lose);
    stack.pushState(States::Pause);
    stack.pushState(States::Level);
    stack.pushState(States::Ranking);
    stack.pushState(States::Saved);
    stack.pushState(States::ChooseMode);
    stack.pushState(States::Menu);

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
