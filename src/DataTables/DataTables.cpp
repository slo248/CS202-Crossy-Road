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
    data[Character::Bee].normalSpeed = 350.f;
    data[Character::Bee].textures = {
        static_cast<Textures::ID>(Textures::BeeToLeft),
        static_cast<Textures::ID>(Textures::BeeToRight),
        static_cast<Textures::ID>(Textures::BeeIdle),
    };
    data[Character::Bee].frameSize = sf::Vector2i(48, 48);
    data[Character::Bee].numFrames = 6;
    /*<-------------------------Bee------------------------------->*/

    /*<-------------------------Bird------------------------------->*/
    data[Character::Bird].normalSpeed = 350.f;
    data[Character::Bird].textures = {
        static_cast<Textures::ID>(Textures::BirdToLeft),
        static_cast<Textures::ID>(Textures::BirdToRight),
        static_cast<Textures::ID>(Textures::BirdIdle),
    };
    data[Character::Bird].frameSize = sf::Vector2i(48, 48);
    data[Character::Bird].numFrames = 4;
    /*<-------------------------Bird------------------------------->*/

    /*<-------------------------BeeBoss--------------------------->*/
    data[Character::BeeBoss].normalSpeed = 350.f;
    data[Character::BeeBoss].textures = {
        static_cast<Textures::ID>(Textures::BeeBossToLeft),
        static_cast<Textures::ID>(Textures::BeeBossToRight),
        static_cast<Textures::ID>(Textures::BeeBossIdle),
    };
    data[Character::BeeBoss].frameSize = sf::Vector2i(96, 96);
    data[Character::BeeBoss].numFrames = 6;
    /*<-------------------------BeeBoss--------------------------->*/

    /*<-------------------------BombBat--------------------------->*/
    data[Character::BombBat].normalSpeed = 350.f;
    data[Character::BombBat].textures = {
        static_cast<Textures::ID>(Textures::BombBatToLeft),
        static_cast<Textures::ID>(Textures::BombBatToRight),
        static_cast<Textures::ID>(Textures::BombBatIdle),
    };
    data[Character::BombBat].frameSize = sf::Vector2i(48, 48);
    data[Character::BombBat].numFrames = 6;
    /*<-------------------------BombBat--------------------------->*/

    /*<-------------------------Crocodile------------------------->*/
    data[Character::Crocodile].normalSpeed = 150.f;
    data[Character::Crocodile].textures = {
        static_cast<Textures::ID>(Textures::CrocodileToLeft),
        static_cast<Textures::ID>(Textures::CrocodileToRight),
        static_cast<Textures::ID>(Textures::CrocodileIdle),
    };
    data[Character::Crocodile].frameSize = sf::Vector2i(48, 48);
    data[Character::Crocodile].numFrames = 6;
    /*<-------------------------Crocodile------------------------->*/

    /*<-------------------------Dog------------------------->*/
    data[Character::Dog].normalSpeed = 150.f;
    data[Character::Dog].textures = {
        static_cast<Textures::ID>(Textures::DogToLeft),
        static_cast<Textures::ID>(Textures::DogToRight),
        static_cast<Textures::ID>(Textures::DogIdle),
    };
    data[Character::Dog].frameSize = sf::Vector2i(48, 48);
    data[Character::Dog].numFrames = 6;
    /*<-------------------------Dog------------------------->*/

    /*<-------------------------Frog------------------------->*/
    data[Character::Frog].normalSpeed = 150.f;
    data[Character::Frog].textures = {
        static_cast<Textures::ID>(Textures::FrogToLeft),
        static_cast<Textures::ID>(Textures::FrogToRight),
        static_cast<Textures::ID>(Textures::FrogIdle),
    };
    data[Character::Frog].frameSize = sf::Vector2i(48, 48);
    data[Character::Frog].numFrames = 4;
    /*<-------------------------Frog------------------------->*/

    /*<-------------------------Rabbit------------------------->*/
    data[Character::Rabbit].normalSpeed = 150.f;
    data[Character::Rabbit].textures = {
        static_cast<Textures::ID>(Textures::RabbitToLeft),
        static_cast<Textures::ID>(Textures::RabbitToRight),
        static_cast<Textures::ID>(Textures::RabbitIdle),
    };
    data[Character::Rabbit].frameSize = sf::Vector2i(48, 48);
    data[Character::Rabbit].numFrames = 4;
    /*<-------------------------Rabbit------------------------->*/

    /*<-------------------------Sheep------------------------->*/
    data[Character::Sheep].normalSpeed = 150.f;
    data[Character::Sheep].textures = {
        static_cast<Textures::ID>(Textures::SheepToLeft),
        static_cast<Textures::ID>(Textures::SheepToRight),
        static_cast<Textures::ID>(Textures::SheepIdle),
    };
    data[Character::Sheep].frameSize = sf::Vector2i(48, 48);
    data[Character::Sheep].numFrames = 4;
    /*<-------------------------Sheep------------------------->*/

    /*<-------------------------Turtle------------------------->*/
    data[Character::Turtle].normalSpeed = 150.f;
    data[Character::Turtle].textures = {
        static_cast<Textures::ID>(Textures::TurtleToLeft),
        static_cast<Textures::ID>(Textures::TurtleToRight),
        static_cast<Textures::ID>(Textures::TurtleIdle),
    };
    data[Character::Turtle].frameSize = sf::Vector2i(48, 48);
    data[Character::Turtle].numFrames = 6;
    /*<-------------------------Turtle------------------------->*/

    /*<-------------------------Fishmen------------------------->*/
    data[Character::Fishmen].normalSpeed = 150.f;
    data[Character::Fishmen].textures = {
        static_cast<Textures::ID>(Textures::FishmenToLeft),
        static_cast<Textures::ID>(Textures::FishmenToRight),
        static_cast<Textures::ID>(Textures::FishmenIdle),
    };
    data[Character::Fishmen].frameSize = sf::Vector2i(48, 48);
    data[Character::Fishmen].numFrames = 6;
    /*<-------------------------Fishmen------------------------->*/

    /*<-------------------------Orc------------------------->*/
    data[Character::Orc].normalSpeed = 150.f;
    data[Character::Orc].textures = {
        static_cast<Textures::ID>(Textures::OrcToLeft),
        static_cast<Textures::ID>(Textures::OrcToRight),
        static_cast<Textures::ID>(Textures::OrcIdle),
    };
    data[Character::Orc].frameSize = sf::Vector2i(96, 96);
    data[Character::Orc].numFrames = 6;
    /*<-------------------------Orc------------------------->*/

    /*<-------------------------Zombie------------------------->*/
    data[Character::Zombie].normalSpeed = 150.f;
    data[Character::Zombie].textures = {
        static_cast<Textures::ID>(Textures::ZombieToLeft),
        static_cast<Textures::ID>(Textures::ZombieToRight),
        static_cast<Textures::ID>(Textures::ZombieIdle),
    };
    data[Character::Zombie].frameSize = sf::Vector2i(48, 48);
    data[Character::Zombie].numFrames = 6;
    /*<-------------------------Zombie------------------------->*/

    // Skin data
    for (int i = Character::Archer; i < Character::TypeCount; ++i) {
        data[i].normalSpeed = 0.f;
        int tmp = 4 * i;
        data[i].textures = {
            static_cast<Textures::ID>(Textures::ArcherToLeft + tmp),
            static_cast<Textures::ID>(Textures::ArcherToRight + tmp),
            static_cast<Textures::ID>(Textures::ArcherIdle + tmp),
            static_cast<Textures::ID>(Textures::ArcherDead + tmp),
        };
        data[i].frameSize = DEFAULT_CELL_RECT.getSize();
        data[i].numFrames = 4;
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

    data[Obstacle::Type::River_Log1].normalSpeed = 100.f;
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
