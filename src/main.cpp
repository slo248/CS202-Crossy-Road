#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Player.hpp"
#include "ResourceHolder.hpp"
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
    bool isNewGame;
    std::cout << "New game? (1 or 0) ";
    std::cin >> isNewGame;
    World world(textures, fonts, window, Config::GameLevel::L1, !isNewGame);
    Player player;

    sf::Clock clock;
    // sf::Time dt = sf::Time::Zero;
    while (window.isOpen()) {
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
