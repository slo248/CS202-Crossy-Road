#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Resources");
    window.setFramerateLimit(20);

    // Try to load resources
    ResourceHolder<sf::Texture, Textures::ID> textures;
    try {
        textures.load(
            Textures::bom_bats, "asset/s_vehicles/bombbats/Boom1.png"
        );
        textures.load(Textures::bee_boss, "asset/s_vehicles/bees/D_Attack.png");
    } catch (std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

    // Access resources
    sf::Sprite bombats(textures.get(Textures::bom_bats));
    sf::Sprite beeboss(textures.get(Textures::bee_boss));
    beeboss.setPosition(200.f, 200.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::Closed)
                return 0;
        }

        window.clear();
        window.draw(bombats);
        window.draw(beeboss);
        window.display();
    }
}
