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
    data[Character::BeeBoss].frameSize = sf::Vector2i(42, 50);
    data[Character::BeeBoss].numFrames = 6;
    /*<-------------------------BeeBoss--------------------------->*/

    /*<-------------------------BombBat--------------------------->*/
    data[Character::BombBat].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::BombBat].textures = {
        Textures::BombBatToLeft,
        Textures::BombBatToRight,
        Textures::BombBatIdle,
    };
    data[Character::BombBat].frameSize = sf::Vector2i(52, 44);
    data[Character::BombBat].numFrames = 6;
    /*<-------------------------BombBat--------------------------->*/

    /*<-------------------------Crocodile------------------------->*/
    data[Character::Crocodile].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Crocodile].textures = {
        Textures::CrocodileToLeft,
        Textures::CrocodileToRight,
        Textures::CrocodileIdle,
    };
    data[Character::Crocodile].frameSize = sf::Vector2i(72, 72);
    data[Character::Crocodile].numFrames = 6;
    /*<-------------------------Crocodile------------------------->*/

    /*<-------------------------Dog------------------------->*/
    data[Character::Dog].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Dog].textures = {
        Textures::DogToLeft,
        Textures::DogToRight,
        Textures::DogIdle,
    };
    data[Character::Dog].frameSize = sf::Vector2i(46, 40);
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
    data[Character::Fishmen].frameSize = sf::Vector2i(42, 44);
    data[Character::Fishmen].numFrames = 6;
    /*<-------------------------Fishmen------------------------->*/

    /*<-------------------------Orc------------------------->*/
    data[Character::Orc].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Orc].textures = {
        Textures::OrcToLeft,
        Textures::OrcToRight,
        Textures::OrcIdle,
    };
    data[Character::Orc].frameSize = sf::Vector2i(54, 54);
    data[Character::Orc].numFrames = 6;
    /*<-------------------------Orc------------------------->*/

    /*<-------------------------Zombie------------------------->*/
    data[Character::Zombie].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Zombie].textures = {
        Textures::ZombieToLeft,
        Textures::ZombieToRight,
        Textures::ZombieIdle,
    };
    data[Character::Zombie].frameSize = sf::Vector2i(42, 44);
    data[Character::Zombie].numFrames = 6;
    /*<-------------------------Zombie------------------------->*/

    /*<-------------------------Wraith------------------------->*/
    data[Character::Wraith].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Wraith].textures = {
        Textures::WraithToLeft,
        Textures::WraithToRight,
        Textures::WraithIdle,
    };
    data[Character::Wraith].frameSize = sf::Vector2i(44,50);
    data[Character::Wraith].numFrames = 10;
    /*<-------------------------Wraith------------------------->*/

    /*<-------------------------WraithPro------------------------->*/
    data[Character::WraithPro].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::WraithPro].textures = {
        Textures::WraithProToLeft,
        Textures::WraithProToRight,
        Textures::WraithProIdle,
    };
    data[Character::WraithPro].frameSize = sf::Vector2i(44,50);
    data[Character::WraithPro].numFrames = 10;
    /*<-------------------------WraithPro------------------------->*/

    /*<-------------------------WraithSwamp------------------------->*/
    data[Character::WraithSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::WraithSwamp].textures = {
        Textures::WraithSwampToLeft,
        Textures::WraithSwampToRight,
        Textures::WraithSwampIdle,
    };
    data[Character::WraithSwamp].frameSize = sf::Vector2i(44,50);
    data[Character::WraithSwamp].numFrames = 10;
    /*<-------------------------WraithSwamp------------------------->*/

    /*<-------------------------GolemGy------------------------->*/
    data[Character::GolemGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::GolemGy].textures = {
        Textures::GolemGyToLeft,
        Textures::GolemGyToRight,
        Textures::GolemGyIdle,
    };
    data[Character::GolemGy].frameSize = sf::Vector2i(60,50);
    data[Character::GolemGy].numFrames = 10;
    /*<-------------------------GolemGy------------------------->*/

    /*<-------------------------Golem------------------------->*/
    data[Character::Golem].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Golem].textures = {
        Textures::GolemToLeft,
        Textures::GolemToRight,
        Textures::GolemIdle,
    };
    data[Character::Golem].frameSize = sf::Vector2i(60,50);
    data[Character::Golem].numFrames = 10;
    /*<-------------------------Golem------------------------->*/

    /*<-------------------------GolemSwamp------------------------->*/
    data[Character::GolemSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::GolemSwamp].textures = {
        Textures::GolemSwampToLeft,
        Textures::GolemSwampToRight,
        Textures::GolemSwampIdle,
    };
    data[Character::GolemSwamp].frameSize = sf::Vector2i(60,50);
    data[Character::GolemSwamp].numFrames = 10;
    /*<-------------------------GolemSwamp------------------------->*/

    /*<-------------------------SatyrGy------------------------->*/
    data[Character::SatyrGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::SatyrGy].textures = {
        Textures::SatyrGyToLeft,
        Textures::SatyrGyToRight,
        Textures::SatyrGyIdle,
    };
    data[Character::SatyrGy].frameSize = sf::Vector2i(48,48);
    data[Character::SatyrGy].numFrames = 10;
    /*<-------------------------SatyrGy------------------------->*/

    /*<-------------------------Satyr------------------------->*/
    data[Character::Satyr].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Satyr].textures = {
        Textures::SatyrToLeft,
        Textures::SatyrToRight,
        Textures::SatyrIdle,
    };
    data[Character::Satyr].frameSize = sf::Vector2i(48,48);
    data[Character::Satyr].numFrames = 10;
    /*<-------------------------Satyr------------------------->*/

    /*<-------------------------SatyrSwamp------------------------->*/
    data[Character::SatyrSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::SatyrSwamp].textures = {
        Textures::SatyrSwampToLeft,
        Textures::SatyrSwampToRight,
        Textures::SatyrSwampIdle,
    };
    data[Character::SatyrSwamp].frameSize = sf::Vector2i(48,48);
    data[Character::SatyrSwamp].numFrames = 10;
    /*<-------------------------SatyrSwamp------------------------->*/

    /*<-------------------------MinoGy------------------------->*/
    data[Character::MinoGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::MinoGy].textures = {
        Textures::MinoGyToLeft,
        Textures::MinoGyToRight,
        Textures::MinoGyIdle,
    };
    data[Character::MinoGy].frameSize = sf::Vector2i(58,56);
    data[Character::MinoGy].numFrames = 10;
    /*<-------------------------MinoGy------------------------->*/

    /*<-------------------------Mino------------------------->*/
    data[Character::Mino].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Mino].textures = {
        Textures::MinoToLeft,
        Textures::MinoToRight,
        Textures::MinoIdle,
    };
    data[Character::Mino].frameSize = sf::Vector2i(58,56);
    data[Character::Mino].numFrames = 10;
    /*<-------------------------Mino------------------------->*/

    /*<-------------------------MinoSwamp------------------------->*/
    data[Character::MinoSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::MinoSwamp].textures = {
        Textures::MinoSwampToLeft,
        Textures::MinoSwampToRight,
        Textures::MinoSwampIdle,
    };
    data[Character::MinoSwamp].frameSize = sf::Vector2i(58,56);
    data[Character::MinoSwamp].numFrames = 10;
    /*<-------------------------MinoSwamp------------------------->*/

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
        data[i].frameSize = sf::Vector2i(42, 38);
        data[i].numFrames = 3;
    }

    return data;
}

std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);

    for (int i = 0; i < Obstacle::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::Field_Bush2 + i);
        data[i].textureRect = DEFAULT_CELL_RECT;
        data[i].normalSpeed = 0.f;
    }

    data[Obstacle::Type::River_Log1].normalSpeed = DEFAULT_LOG_SPEED;

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
