#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "World.hpp"

void loadTexture(TextureHolder& textures) {
    /***************************Load Animal Textures***************************/
    textures.load(
        Textures::BeeToLeft, "asset/game_textures/Animal/Bee/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::BeeToRight,
        "asset/game_textures/Animal/Bee/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::BeeIdle, "asset/game_textures/Animal/Bee/D_Walk.png"
    );

    textures.load(
        Textures::BirdToLeft,
        "asset/game_textures/Animal/Bird1/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BirdToRight,
        "asset/game_textures/Animal/Bird1/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::BirdIdle, "asset/game_textures/Animal/Bird1/D_Fly.png"
    );

    textures.load(
        Textures::CrocodileToLeft,
        "asset/game_textures/Animal/Crocodile/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::CrocodileToRight,
        "asset/game_textures/Animal/Crocodile/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::CrocodileIdle,
        "asset/game_textures/Animal/Crocodile/D_Walk.png"
    );

    textures.load(
        Textures::DogToLeft, "asset/game_textures/Animal/Dog/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::DogToRight,
        "asset/game_textures/Animal/Dog/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::DogIdle, "asset/game_textures/Animal/Dog/D_Walk.png"
    );

    textures.load(
        Textures::FrogToLeft,
        "asset/game_textures/Animal/Frog/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::FrogToRight,
        "asset/game_textures/Animal/Frog/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::FrogIdle, "asset/game_textures/Animal/Frog/D_Walk.png"
    );

    textures.load(
        Textures::RabbitToLeft,
        "asset/game_textures/Animal/Rabbit/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::RabbitToRight,
        "asset/game_textures/Animal/Rabbit/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::RabbitIdle, "asset/game_textures/Animal/Rabbit/D_Walk.png"
    );

    textures.load(
        Textures::SheepToLeft,
        "asset/game_textures/Animal/Sheep/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::SheepToRight,
        "asset/game_textures/Animal/Sheep/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::SheepIdle, "asset/game_textures/Animal/Sheep/D_Walk.png"
    );

    textures.load(
        Textures::TurtleToLeft,
        "asset/game_textures/Animal/Turtle/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::TurtleToRight,
        "asset/game_textures/Animal/Turtle/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::TurtleIdle, "asset/game_textures/Animal/Turtle/D_Walk.png"
    );

    /*************************************************************************/

    /***********************Load TrafficLight Textures***********************/
    textures.load(
        Textures::Field_TrafficLight,
        "asset/game_textures/TrafficLight/Field_TrafficLight.png"
    );
    textures.load(
        Textures::Graveyard_TrafficLight,
        "asset/game_textures/TrafficLight/Graveyard_TrafficLight.png"
    );
    textures.load(
        Textures::Swamp_TrafficLight,
        "asset/game_textures/TrafficLight/Swamp_TrafficLight.png"
    );
    /*************************************************************************/

    /***********************Load Enemy Textures****************************/
    textures.load(
        Textures::BeeBossToLeft,
        "asset/game_textures/Enemy/BeeBoss/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BeeBossToRight,
        "asset/game_textures/Enemy/BeeBoss/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::BeeBossIdle, "asset/game_textures/Enemy/BeeBoss/D_Fly.png"
    );

    textures.load(
        Textures::BombBatToLeft,
        "asset/game_textures/Enemy/BombBat/S_Fly_ToLeft.png"
    );
    textures.load(
        Textures::BombBatToRight,
        "asset/game_textures/Enemy/BombBat/S_Fly_ToRight.png"
    );
    textures.load(
        Textures::BombBatIdle, "asset/game_textures/Enemy/BombBat/D_Fly.png"
    );

    textures.load(
        Textures::FishmenToLeft,
        "asset/game_textures/Enemy/Fishmen/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::FishmenToRight,
        "asset/game_textures/Enemy/Fishmen/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::FishmenIdle, "asset/game_textures/Enemy/Fishmen/D_Walk.png"
    );

    textures.load(
        Textures::OrcToLeft, "asset/game_textures/Enemy/Orc/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::OrcToRight, "asset/game_textures/Enemy/Orc/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::OrcIdle, "asset/game_textures/Enemy/Orc/D_Walk.png"
    );

    textures.load(
        Textures::ZombieToLeft,
        "asset/game_textures/Enemy/Zombie/S_Walk_ToLeft.png"
    );
    textures.load(
        Textures::ZombieToRight,
        "asset/game_textures/Enemy/Zombie/S_Walk_ToRight.png"
    );
    textures.load(
        Textures::ZombieIdle, "asset/game_textures/Enemy/Zombie/D_Walk.png"
    );
    /*************************************************************************/

    /**************************Load Lane Textures******************************/
    textures.load(Textures::Dirt, "asset/game_textures/Lane/Dirt64.png");
    textures.load(Textures::Grass, "asset/game_textures/Lane/Grass64.png");
    textures.load(
        Textures::Graveyard, "asset/game_textures/Lane/Graveyard64.png"
    );
    textures.load(Textures::Soil, "asset/game_textures/Lane/Soil64.png");
    textures.load(Textures::Swamp, "asset/game_textures/Lane/Swamp64.png");
    textures.load(Textures::River, "asset/game_textures/Lane/River64.png");
    /*************************************************************************/

    /**************************Load Skin Textures************************/
    textures.load(
        Textures::ArcherToLeft,
        "asset/game_textures/Skin/Archer/Walk_ToLeft.png"
    );
    textures.load(
        Textures::ArcherToRight,
        "asset/game_textures/Skin/Archer/Walk_ToRight.png"
    );
    textures.load(
        Textures::ArcherIdle, "asset/game_textures/Skin/Archer/Idle64.png"
    );
    textures.load(
        Textures::ArcherDead, "asset/game_textures/Skin/Archer/Dead.png"
    );

    textures.load(
        Textures::EnchantressToLeft,
        "asset/game_textures/Skin/Enchantress/Walk_ToLeft.png"
    );
    textures.load(
        Textures::EnchantressToRight,
        "asset/game_textures/Skin/Enchantress/Walk_ToRight.png"
    );
    textures.load(
        Textures::EnchantressIdle,
        "asset/game_textures/Skin/Enchantress/Idle.png"
    );
    textures.load(
        Textures::EnchantressDead,
        "asset/game_textures/Skin/Enchantress/Dead.png"
    );

    textures.load(
        Textures::KnightToLeft,
        "asset/game_textures/Skin/Knight/Walk_ToLeft.png"
    );
    textures.load(
        Textures::KnightToRight,
        "asset/game_textures/Skin/Knight/Walk_ToRight.png"
    );
    textures.load(
        Textures::KnightIdle, "asset/game_textures/Skin/Knight/Idle.png"
    );
    textures.load(
        Textures::KnightDead, "asset/game_textures/Skin/Knight/Dead.png"
    );

    textures.load(
        Textures::MusketeerToLeft,
        "asset/game_textures/Skin/Musketeer/Walk_ToLeft.png"
    );
    textures.load(
        Textures::MusketeerToRight,
        "asset/game_textures/Skin/Musketeer/Walk_ToRight.png"
    );
    textures.load(
        Textures::MusketeerIdle, "asset/game_textures/Skin/Musketeer/Idle.png"
    );
    textures.load(
        Textures::MusketeerDead, "asset/game_textures/Skin/Musketeer/Dead.png"
    );

    textures.load(
        Textures::SwordsmanToLeft,
        "asset/game_textures/Skin/Swordsman/Walk_ToLeft.png"
    );
    textures.load(
        Textures::SwordsmanToRight,
        "asset/game_textures/Skin/Swordsman/Walk_ToRight.png"
    );
    textures.load(
        Textures::SwordsmanIdle, "asset/game_textures/Skin/Swordsman/Idle.png"
    );
    textures.load(
        Textures::SwordsmanDead, "asset/game_textures/Skin/Swordsman/Dead.png"
    );

    textures.load(
        Textures::WizardToLeft,
        "asset/game_textures/Skin/Wizard/Walk_ToLeft.png"
    );
    textures.load(
        Textures::WizardToRight,
        "asset/game_textures/Skin/Wizard/Walk_ToRight.png"
    );
    textures.load(
        Textures::WizardIdle, "asset/game_textures/Skin/Wizard/Idle.png"
    );
    textures.load(
        Textures::WizardDead, "asset/game_textures/Skin/Wizard/Dead.png"
    );
    /***********************************************************************/

    /**************************Load Other Textures**************************/

    /*<------------------------Field Textures--------------------------->*/
    textures.load(
        Textures::Field_Bush2,
        "asset/game_textures/Obstacle/Field/Bush/Bush2.png"
    );
    textures.load(
        Textures::Field_Lamp1,
        "asset/game_textures/Obstacle/Field/Lamp/Lamp1.png"
    );
    textures.load(
        Textures::Field_Stone6,
        "asset/game_textures/Obstacle/Field/Stone/Stone6.png"
    );
    textures.load(
        Textures::Field_Tent3,
        "asset/game_textures/Obstacle/Field/Tent/Tent3.png"
    );
    textures.load(
        Textures::Field_Tree1,
        "asset/game_textures/Obstacle/Field/Tree/Tree1.png"
    );
    /*<------------------------Field Textures--------------------------->*/

    /*<------------------------Graveyard Textures--------------------------->*/
    textures.load(
        Textures::Graveyard_House1,
        "asset/game_textures/Obstacle/Graveyard/House/House1.png"
    );
    textures.load(
        Textures::Graveyard_Statue8,
        "asset/game_textures/Obstacle/Graveyard/Statue/Statue8.png"
    );
    textures.load(
        Textures::Graveyard_Tree2,
        "asset/game_textures/Obstacle/Graveyard/Tree/Tree2.png"
    );
    /*<------------------------Graveyard Textures--------------------------->*/

    /*<------------------------Swamp Textures--------------------------->*/
    textures.load(
        Textures::Swamp_House1,
        "asset/game_textures/Obstacle/Swamp/House/House1.png"
    );
    textures.load(
        Textures::Swamp_Tree2,
        "asset/game_textures/Obstacle/Swamp/Tree/Tree2.png"
    );
    textures.load(
        Textures::Swamp_Well1,
        "asset/game_textures/Obstacle/Swamp/Well/Well1.png"
    );
    /*<------------------------Swamp Textures--------------------------->*/

    /*<------------------------River Textures--------------------------->*/
    textures.load(
        Textures::River_Log1, "asset/game_textures/Obstacle/River/Log/Log2.png"
    );
    /*<------------------------River Textures--------------------------->*/
}

int main() {
    srand(time(0));
    sf::RenderWindow window(
        sf::VideoMode(DEFAULT_CELL_LENGTH * 14, DEFAULT_CELL_LENGTH * 10),
        "Pro Game", sf::Style::Default
    );
    window.setFramerateLimit(60);

    TextureHolder textures;
    FontHolder fonts;

    loadTexture(textures);
    World world(textures, fonts, window, Config::GameLevel::L1);
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

        window.clear(sf::Color::White);
        world.draw();
        window.display();
    }

    return 0;
}
