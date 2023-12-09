#include "DataTables.hpp"

#include "Character.hpp"
#include "Lane.hpp"
#include "Obstacle.hpp"
#include "TrafficLight.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CharacterData> initializeCharacterData() {
    std::vector<CharacterData> data(Character::TypeCount);

    // Enemy data
    // Air enemy data
    /*<-------------------------Bee------------------------------->*/
    data[Character::Bee].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::Bee].textures = {
        Textures::BeeToLeft,
        Textures::BeeToRight,
        Textures::BeeIdle,
    };
    data[Character::Bee].frameSize = sf::Vector2i(48, 48);
    data[Character::Bee].numFrames = 6;
    /*<-------------------------Bee------------------------------->*/

    /*<-------------------------Bird------------------------------->*/
    data[Character::Bird].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::Bird].textures = {
        Textures::BirdToLeft,
        Textures::BirdToRight,
        Textures::BirdIdle,
    };
    data[Character::Bird].frameSize = sf::Vector2i(48, 48);
    data[Character::Bird].numFrames = 4;
    /*<-------------------------Bird------------------------------->*/

    /*<-------------------------BeeBoss--------------------------->*/
    data[Character::BeeBoss].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::BeeBoss].textures = {
        Textures::BeeBossToLeft,
        Textures::BeeBossToRight,
        Textures::BeeBossIdle,
    };
    data[Character::BeeBoss].frameSize = sf::Vector2i(96, 96);
    data[Character::BeeBoss].numFrames = 6;
    /*<-------------------------BeeBoss--------------------------->*/

    /*<-------------------------BombBat--------------------------->*/
    data[Character::BombBat].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::BombBat].textures = {
        Textures::BombBatToLeft,
        Textures::BombBatToRight,
        Textures::BombBatIdle,
    };
    data[Character::BombBat].frameSize = sf::Vector2i(48, 48);
    data[Character::BombBat].numFrames = 6;
    /*<-------------------------BombBat--------------------------->*/

    /*<-------------------------Crocodile------------------------->*/
    data[Character::Crocodile].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Crocodile].textures = {
        Textures::CrocodileToLeft,
        Textures::CrocodileToRight,
        Textures::CrocodileIdle,
    };
    data[Character::Crocodile].frameSize = sf::Vector2i(48, 48);
    data[Character::Crocodile].numFrames = 6;
    /*<-------------------------Crocodile------------------------->*/

    /*<-------------------------Dog------------------------->*/
    data[Character::Dog].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Dog].textures = {
        Textures::DogToLeft,
        Textures::DogToRight,
        Textures::DogIdle,
    };
    data[Character::Dog].frameSize = sf::Vector2i(48, 48);
    data[Character::Dog].numFrames = 6;
    /*<-------------------------Dog------------------------->*/

    /*<-------------------------Frog------------------------->*/
    data[Character::Frog].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Frog].textures = {
        Textures::FrogToLeft,
        Textures::FrogToRight,
        Textures::FrogIdle,
    };
    data[Character::Frog].frameSize = sf::Vector2i(48, 48);
    data[Character::Frog].numFrames = 4;
    /*<-------------------------Frog------------------------->*/

    /*<-------------------------Rabbit------------------------->*/
    data[Character::Rabbit].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Rabbit].textures = {
        Textures::RabbitToLeft,
        Textures::RabbitToRight,
        Textures::RabbitIdle,
    };
    data[Character::Rabbit].frameSize = sf::Vector2i(48, 48);
    data[Character::Rabbit].numFrames = 4;
    /*<-------------------------Rabbit------------------------->*/

    /*<-------------------------Sheep------------------------->*/
    data[Character::Sheep].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Sheep].textures = {
        Textures::SheepToLeft,
        Textures::SheepToRight,
        Textures::SheepIdle,
    };
    data[Character::Sheep].frameSize = sf::Vector2i(48, 48);
    data[Character::Sheep].numFrames = 4;
    /*<-------------------------Sheep------------------------->*/

    /*<-------------------------Turtle------------------------->*/
    data[Character::Turtle].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Turtle].textures = {
        Textures::TurtleToLeft,
        Textures::TurtleToRight,
        Textures::TurtleIdle,
    };
    data[Character::Turtle].frameSize = sf::Vector2i(48, 48);
    data[Character::Turtle].numFrames = 6;
    /*<-------------------------Turtle------------------------->*/

    /*<-------------------------Fishmen------------------------->*/
    data[Character::Fishmen].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Fishmen].textures = {
        Textures::FishmenToLeft,
        Textures::FishmenToRight,
        Textures::FishmenIdle,
    };
    data[Character::Fishmen].frameSize = sf::Vector2i(48, 48);
    data[Character::Fishmen].numFrames = 6;
    /*<-------------------------Fishmen------------------------->*/

    /*<-------------------------Orc------------------------->*/
    data[Character::Orc].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Orc].textures = {
        Textures::OrcToLeft,
        Textures::OrcToRight,
        Textures::OrcIdle,
    };
    data[Character::Orc].frameSize = sf::Vector2i(96, 96);
    data[Character::Orc].numFrames = 6;
    /*<-------------------------Orc------------------------->*/

    /*<-------------------------Zombie------------------------->*/
    data[Character::Zombie].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Zombie].textures = {
        Textures::ZombieToLeft,
        Textures::ZombieToRight,
        Textures::ZombieIdle,
    };
    data[Character::Zombie].frameSize = sf::Vector2i(48, 48);
    data[Character::Zombie].numFrames = 6;
    /*<-------------------------Zombie------------------------->*/

    // Skin data
    for (int i = Character::Archer; i < Character::TypeCount; ++i) {
        data[i].normalSpeed = DEFAULT_PLAYER_SPEED;
        int tmp = 4 * (i - Character::Archer);
        data[i].textures = {
            static_cast<Textures::ID>(Textures::ArcherToLeft + tmp),
            static_cast<Textures::ID>(Textures::ArcherToRight + tmp),
            static_cast<Textures::ID>(Textures::ArcherIdle + tmp),
            static_cast<Textures::ID>(Textures::ArcherDead + tmp),
        };
        // data[i].frameSize = DEFAULT_CELL_RECT.getSize();
        data[i].frameSize = sf::Vector2i(110, 64);
        data[i].numFrames = 6;
    }

    return data;
}

std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);

    for (int i = 0; i < Obstacle::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::Field_Bush2 + i);
        data[i].textureRect = DEFAULT_CELL_RECT;
        data[i].isBlockingPlayer = true;
        data[i].normalSpeed = 0.f;
    }

    data[Obstacle::Type::River_Log1].normalSpeed = DEFAULT_LOG_SPEED;
    data[Obstacle::Type::River_Log1].isBlockingPlayer = false;

    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data(LaneType::TypeCount);

    for (int i = 0; i < LaneType::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::Dirt + i);
        data[i].textureRect = DEFAULT_LANE_RECT;
        data[i].spawnInterval = DEFAULT_SPAWN_INTERVAL;
    }

    return data;
}

std::vector<TrafficLightData> initializeTrafficLightData() {
    std::vector<TrafficLightData> data(TrafficLight::Type::TypeCount);

    for (int i = 0; i < TrafficLight::Type::TypeCount; ++i) {
        data[i].texture =
            static_cast<Textures::ID>(Textures::Field_TrafficLight + i);
        data[i].textureRect = sf::IntRect(0, 0, 48, 64);
    }

    return data;
}
