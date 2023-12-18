#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ChooseModeState.hpp"
#include "Config.hpp"
#include "CreditState.hpp"
#include "LevelState.hpp"
#include "LoseState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "Player.hpp"
#include "RankingState.hpp"
#include "ResourceHolder.hpp"
#include "SettingState.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "WinState.hpp"
#include "World.hpp"

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

    Player player;

    /*<----------------------------Load ranking------------------------>*/
    std::ifstream in(RANKING_PATH);
    if (!in.good()) {
        std::cout << "No ranking file";
        return 0;
    }

    std::vector<int> highScores(DEFAULT_RANKING_SLOTS, 0);
    for (int i = 0; i < DEFAULT_RANKING_SLOTS && in.good(); ++i) {
        int score;
        in >> score;
        highScores[i] = score;
    }

    in.close();
    /*<----------------------------Load ranking------------------------>*/

    State::Context context(window, textures, fonts, player, highScores);
    StateStack stack(context);

    /*<--------------------------GAME TESTING--------------------------->*/

    // bool isNewGame;
    // std::cout << "New game? (1 or 0) ";
    // std::cin >> isNewGame;
    // World world(textures, fonts, window, Config::GameLevel::L1, !isNewGame);
    //
    //     sf::Clock clock;
    //     // sf::Time dt = sf::Time::Zero;
    //     while (stack.mContext.window->isOpen()) {
    //         stack.update(sf::seconds(1.f / 60.f));
    //         stack.mContext.window->clear(sf::Color::White);
    //         sf::Event event;
    //         while (window.pollEvent(event)) {
    //             if (event.type == sf::Event::Closed) window.close();
    //             player.handleEvent(event, world.getCommandQueue());
    //         }
    //         player.handleRealtimeInput(world.getCommandQueue());
    //         // dt += clock.restart();
    //         // while (dt >= sf::seconds(1)) {
    //         //     world.update(sf::seconds(1));
    //         //     dt -= sf::seconds(1);
    //         // }
    //         world.update(clock.restart());
    //         if (!world.hasAlivePlayer()) {
    //             std::cout << "Game Over!\n";
    //             window.close();
    //         }

    //         window.clear(sf::Color::White);
    //         world.draw();
    //         window.display();
    //     }

    //     if (world.hasAlivePlayer()) world.save();
    //     std::cout << "Game exited successfully!\n";

    /*<---------------------------GUI TESTING---------------------------->*/

    stack.registerState<SettingState>(States::Setting);
    // stack.registerState<SettingState>(States::SettingInGame);
    stack.registerState<CreditState>(States::Credit);
    stack.registerState<LoseState>(States::Lose);
    stack.registerState<WinState>(States::Win);
    stack.registerState<PauseState>(States::Pause);
    stack.registerState<MenuState>(States::Menu);
    stack.registerState<RankingState>(States::Ranking);
    stack.registerState<LevelState>(States::Level);
    stack.registerState<ChooseModeState>(States::ChooseMode);
    // stack.registerState<ChooseModeState>(States::ChooseModeSaved);

    stack.pushState(States::Menu);

    while (stack.mContext.window->isOpen()) {
        stack.update(sf::seconds(1.f / 60.f));
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
