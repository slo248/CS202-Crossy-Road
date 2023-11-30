#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimationList.hpp"

void loadTexture(TextureHolder& textures) {
    /***************************Load Animal Textures***************************/
    textures.load(Textures::BeeToLeft, "asset/s_animals/bee/S_Walk_ToLeft.png");
    textures.load(
        Textures::BeeToRight, "asset/s_animals/bee/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::BirdToLeft, "asset/s_animals/bird_1/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BirdToRight, "asset/s_animals/bird_1/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::CrocodileToLeft, "asset/s_animals/crocodile/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::CrocodileToRight,
        "asset/s_animals/crocodile/S_Walk_ToRight.png"
    );
    textures.load(Textures::DogToLeft, "asset/s_animals/dog/S_Walk_ToLeft.png");
    textures.load(
        Textures::DogToRight, "asset/s_animals/dog/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::FrogToLeft, "asset/s_animals/frog/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::FrogToRight, "asset/s_animals/frog/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::RabbitToLeft, "asset/s_animals/rabbit/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::RabbitToRight, "asset/s_animals/rabbit/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::SheepToLeft, "asset/s_animals/sheep/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::SheepToRight, "asset/s_animals/sheep/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::TurtleToLeft, "asset/s_animals/turtle/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::TurtleToRight, "asset/s_animals/turtle/S_Walk_ToRight.png"
    );
    /*************************************************************************/

    /*******************************Load TrafficLight
     * Textures************************************/
    textures.load(
        Textures::FieldTrafficLight,
        "asset/s_traffic_light/field_traffic_light.png"
    );
    textures.load(
        Textures::GraveyardTrafficLight,
        "asset/s_traffic_light/graveyard_traffic_light.png"
    );
    textures.load(
        Textures::SwampTrafficLight,
        "asset/s_traffic_light/swamp_traffic_light.png"
    );
    /*************************************************************************/

    /********************************Load Enemy
     * Textures**********************************/
    textures.load(
        Textures::BeeBossToLeft, "asset/s_enemy/beeboss/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BeeBossToRight, "asset/s_enemy/beeboss/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::BombBatToLeft, "asset/s_enemy/bombbat/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BombBatToRight, "asset/s_enemy/bombbat/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::FishmenToLeft, "asset/s_enemy/fishmen/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::FishmenToRight, "asset/s_enemy/fishmen/S_Walk_ToRight.png"
    );
    textures.load(Textures::OrcToLeft, "asset/s_enemy/orc/S_Walk_ToLeft.png");
    textures.load(Textures::OrcToRight, "asset/s_enemy/orc/S_Walk_ToRight.png");
    textures.load(
        Textures::ZombieToLeft, "asset/s_enemy/zombie/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::ZombieToRight, "asset/s_enemy/zombie/S_Walk_ToRight.png"
    );
    /*************************************************************************/

    /**************************Load Lane Textures******************************/
    textures.load(Textures::River, "asset/s_lane/river.png");
    textures.load(Textures::Dirt, "asset/s_lane/dirt.png");
    textures.load(Textures::Grass, "asset/s_lane/grass.png");
    textures.load(Textures::Graveyard, "asset/s_lane/graveyard.png");
    textures.load(Textures::Soil, "asset/s_lane/soil.png");
    textures.load(Textures::Swamp, "asset/s_lane/swamp.png");
    /*************************************************************************/

    /**************************Load Skin Textures************************/
    textures.load(
        Textures::ArcherToLeft, "asset/s_skin/Archer/Walk_ToLeft.png"
    );
    textures.load(
        Textures::ArcherToRight, "asset/s_skin/Archer/Walk_ToRight.png"
    );
    textures.load(
        Textures::EnchantressToLeft, "asset/s_skin/Enchantress/Walk_ToLeft.png"
    );
    textures.load(
        Textures::EnchantressToRight,
        "asset/s_skin/Enchantress/Walk_ToRight.png"
    );
    textures.load(
        Textures::KnightToLeft, "asset/s_skin/Knight/Walk_ToLeft.png"
    );
    textures.load(
        Textures::KnightToRight, "asset/s_skin/Knight/Walk_ToRight.png"
    );
    textures.load(
        Textures::MusketeerToLeft, "asset/s_skin/Musketeer/Walk_ToLeft.png"
    );
    textures.load(
        Textures::MusketeerToRight, "asset/s_skin/Musketeer/Walk_ToRight.png"
    );
    textures.load(
        Textures::SwordsmanToLeft, "asset/s_skin/Swordsman/Walk_ToLeft.png"
    );
    textures.load(
        Textures::SwordsmanToRight, "asset/s_skin/Swordsman/Walk_ToRight.png"
    );
    textures.load(
        Textures::WizardToLeft, "asset/s_skin/Wizard/Walk_ToLeft.png"
    );
    textures.load(
        Textures::WizardToRight, "asset/s_skin/Wizard/Walk_ToRight.png"
    );
    /***********************************************************************/

    /**************************Load Other Textures**************************/
    textures.load(Textures::bush1, "asset/s_other/Field/Bush/3.png");
    textures.load(Textures::stone1, "asset/s_other/Field/Stone/7.png");
    textures.load(Textures::tree1, "asset/s_other/Field/Decor/Tree1.png");

    textures.load(Textures::gy_tree1, "asset/s_other/Graveyard/Tree/1.png");
    textures.load(Textures::statue1, "asset/s_other/Graveyard/Statue/2.png");
    textures.load(Textures::statue2, "asset/s_other/Graveyard/Statue/30.png");

    textures.load(Textures::well, "asset/s_other/Swamp/Decor/13.png");
    textures.load(Textures::log, "asset/s_other/River/log.png");
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode(1152, 960), "Pro Game", sf::Style::Default
    );
    window.setFramerateLimit(60);

    TextureHolder textures;
    FontHolder fonts;

    loadTexture(textures);

    World world(textures, fonts, window, Config::GameLevel::L1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) switch (event.type) {
                case sf::Event::Closed:
                    std::cout << "Window closed" << std::endl;
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
    greenAnimation->setDuration(sf::seconds(5));
    greenAnimation->setTimePerFrame(sf::seconds(0.25));

    Animation::Ptr yellowAnimation(
        new Animation(yellow, sf::Vector2i(32, 64), 6)
    );
    yellowAnimation->setDuration(sf::seconds(2));
    yellowAnimation->setTimePerFrame(sf::seconds(0.25));

    Animation::Ptr redAnimation(new Animation(red, sf::Vector2i(32, 64), 6));
    redAnimation->setDuration(sf::seconds(4));
    redAnimation->setTimePerFrame(sf::seconds(0.25));

    AnimationList list;
    list.add(std::move(greenAnimation));
    list.add(std::move(yellowAnimation));
    list.add(std::move(redAnimation));

    list.scale(1.5, 1.5);
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
    // AnimationTest();
    AnimationListTest();
    return 0;
}
