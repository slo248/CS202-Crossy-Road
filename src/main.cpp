#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimationList.hpp"

void AnimationTest() {
    sf::Texture bee;
    bee.loadFromFile("asset/s_animals/bee/bee.png");

    Animation beeMoveRight(bee, sf::Vector2i(48, 48), 6);
    beeMoveRight.setDuration(sf::seconds(3));
    beeMoveRight.setTimePerFrame(sf::seconds(0.25));

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
}

void AnimationListTest() {
    sf::Texture green, yellow, red;
    green.loadFromFile("asset/s_traffic/traffic_field_green.png");
    yellow.loadFromFile("asset/s_traffic/traffic_field_yellow.png");
    red.loadFromFile("asset/s_traffic/traffic_field_red.png");

    Animation::Ptr greenAnimation(new Animation(green, sf::Vector2i(32, 64), 6)
    );
    // greenAnimation->setDuration(sf::seconds(2));

    Animation::Ptr yellowAnimation(
        new Animation(yellow, sf::Vector2i(32, 64), 6)
    );
    // yellowAnimation->setDuration(sf::seconds(2));

    Animation::Ptr redAnimation(new Animation(red, sf::Vector2i(32, 64), 6));
    // redAnimation->setDuration(sf::seconds(2));

    AnimationList list;
    list.add(std::move(greenAnimation));
    list.add(std::move(yellowAnimation));
    list.add(std::move(redAnimation));

    list.scale(2, 2);
    list.setPosition(100, 100);

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
                            list.play();
                            break;
                        case sf::Keyboard::B:
                            list.setRepeat(true);
                            break;
                        case sf::Keyboard::S:
                            list.stop();
                            break;
                        default:
                            list.setRepeat(false);
                            break;
                    }
                    break;
            }

        list.update(clock.restart());

        window.clear();
        window.draw(list);
        window.display();
    }
}

int main() {
    AnimationTest();
    // AnimationListTest();
    return 0;
}
