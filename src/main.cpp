#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "World.hpp"

/* #include "ChooseModeState.hpp"
#include "Config.hpp"
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
#include "WinState.hpp" */

int main() {
    srand(time(0));
    sf::RenderWindow window(
        sf::VideoMode(DEFAULT_CELL_LENGTH * 14, DEFAULT_CELL_LENGTH * 10),
        "Pro Game", sf::Style::Default
    );
    window.setFramerateLimit(60);

    TextureHolder textures;
    FontHolder fonts;

    textures.loadTextureFromFile();
    fonts.loadFontFromFile();
    bool isNewGame;
    std::cout << "New game? (1 or 0) ";
    std::cin >> isNewGame;
    World world(textures, fonts, window, Config::GameLevel::L1, !isNewGame);
    Player player;

    sf::Clock clock;
    // sf::Time dt = sf::Time::Zero;
    /* while (window.isOpen()) {
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
    stack.pushState(States::Menu); */

    while (stack.mContext.window->isOpen()) {
        stack.mContext.window->clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            player.handleEvent(event, world.getCommandQueue());
        }
        player.handleRealtimeInput(world.getCommandQueue());
        // dt += clock.restart();
        // while (dt >= sf::seconds(1)) {
        //     world.update(sf::seconds(1));
        //     dt -= sf::seconds(1);
        // }
        world.update(clock.restart());
        if (!world.hasAlivePlayer()) {
            std::cout << "Game Over!\n";
            window.close();
        }

        window.clear(sf::Color::White);
        world.draw();
        window.display();
    }

    if (world.hasAlivePlayer()) world.saveCurrentGame();
    std::cout << "Game exited successfully!\n";

    return 0;
}
