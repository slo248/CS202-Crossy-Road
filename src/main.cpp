#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.hpp"

int main() {
    sf::Texture bee;
    bee.loadFromFile("asset/s_animals/bee/bee.png");

    Animation beeMoveRight(bee, sf::Vector2i(48, 48), 6);
    beeMoveRight.setDuration(sf::seconds(3));

    beeMoveRight.scale(2, 2);
    beeMoveRight.setPosition(100, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Crossy Road");
    window.setFramerateLimit(60);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    std::cout << "Key released!" << std::endl;
                    switch (event.key.code) {
                        case sf::Keyboard::A:
                            // std::cout << "A released" << std::endl;
                            beeMoveRight.play();
                            break;
                        case sf::Keyboard::B:
                            beeMoveRight.setRepeat(true);
                            break;
                        case sf::Keyboard::S:
                            beeMoveRight.stop();
                            break;
                        default:
                            beeMoveRight.setRepeat(false);
                            break;
                    }
                    break;
            }

        beeMoveRight.update(clock.restart());

        window.clear();
        window.draw(beeMoveRight);
        window.display();
    }

    return 0;
}
