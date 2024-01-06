#include "DataTables.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CharacterData> initializeCharacterData() {
    std::vector<CharacterData> data(Character::TypeCount);

    // Animal data
    // /*<-------------------------Bee------------------------------->*/
    // data[Character::Bee].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    // data[Character::Bee].textures = {
    //     Textures::BeeToLeft,
    //     Textures::BeeToRight,
    //     Textures::BeeIdle,
    // };
    // data[Character::Bee].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Bee------------------------------->*/

    // /*<-------------------------Bird------------------------------->*/
    // data[Character::Bird].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    // data[Character::Bird].textures = {
    //     Textures::BirdToLeft,
    //     Textures::BirdToRight,
    //     Textures::BirdIdle,
    // };
    // data[Character::Bird].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Bird------------------------------->*/

    // /*<-------------------------Frog------------------------->*/
    // data[Character::Frog].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    // data[Character::Frog].textures = {
    //     Textures::FrogToLeft,
    //     Textures::FrogToRight,
    //     Textures::FrogIdle,
    // };
    // data[Character::Frog].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Frog------------------------->*/

    // /*<-------------------------Rabbit------------------------->*/
    // data[Character::Rabbit].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    // data[Character::Rabbit].textures = {
    //     Textures::RabbitToLeft,
    //     Textures::RabbitToRight,
    //     Textures::RabbitIdle,
    // };
    // data[Character::Rabbit].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Rabbit------------------------->*/

    // /*<-------------------------Sheep------------------------->*/
    // data[Character::Sheep].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    // data[Character::Sheep].textures = {
    //     Textures::SheepToLeft,
    //     Textures::SheepToRight,
    //     Textures::SheepIdle,
    // };
    // data[Character::Sheep].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Sheep------------------------->*/

    // /*<-------------------------Turtle------------------------->*/
    // data[Character::Turtle].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    // data[Character::Turtle].textures = {
    //     Textures::TurtleToLeft,
    //     Textures::TurtleToRight,
    //     Textures::TurtleIdle,
    // };
    // data[Character::Turtle].frameSize = sf::Vector2i(48, 48);
    // /*<-------------------------Turtle------------------------->*/

    // Enemy data
    /*<-------------------------BeeBoss--------------------------->*/
    data[Character::BeeBoss].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::BeeBoss].textures = {
        Textures::BeeBossToLeft,
        Textures::BeeBossToRight,
        Textures::BeeBossIdle,
        Textures::BeeBossDead,
    };
    data[Character::BeeBoss].frameSize = sf::Vector2i(42, 50);
    data[Character::BeeBoss].isWaterproof = true;
    /*<-------------------------BeeBoss--------------------------->*/

    /*<-------------------------BombBat--------------------------->*/
    data[Character::BombBat].normalSpeed = DEFAULT_AIR_ENEMY_SPEED;
    data[Character::BombBat].textures = {
        Textures::BombBatToLeft,
        Textures::BombBatToRight,
        Textures::BombBatIdle,
        Textures::BombBatDead,
    };
    data[Character::BombBat].frameSize = sf::Vector2i(52, 44);
    data[Character::BeeBoss].isWaterproof = true;
    /*<-------------------------BombBat--------------------------->*/

    /*<-------------------------Bird--------------------------->*/
    data[Character::Bird].normalSpeed = DEFAULT_AIR_ENEMY_SPEED * 0.8;
    data[Character::Bird].textures = {
        Textures::BirdToLeft,
        Textures::BirdToRight,
        Textures::BirdIdle,
        Textures::BirdDead,
    };
    data[Character::Bird].frameSize = sf::Vector2i(42, 48);
    data[Character::Bird].isWaterproof = true;
    /*<-------------------------Bird--------------------------->*/

    /*<-------------------------Crocodile------------------------->*/
    data[Character::Crocodile].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 1.2;
    data[Character::Crocodile].textures = {
        Textures::CrocodileToLeft,
        Textures::CrocodileToRight,
        Textures::CrocodileIdle,
    };
    data[Character::Crocodile].frameSize = sf::Vector2i(54, 32);
    data[Character::Crocodile].isWaterproof = true;
    /*<-------------------------Crocodile------------------------->*/

    /*<-------------------------Dog------------------------->*/
    data[Character::Dog].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.9;
    data[Character::Dog].textures = {
        Textures::DogToLeft,
        Textures::DogToRight,
        Textures::DogIdle,
    };
    data[Character::Dog].frameSize = sf::Vector2i(46, 40);
    data[Character::Dog].isWaterproof = true;
    /*<-------------------------Dog------------------------->*/

    /*<-------------------------Fishmen------------------------->*/
    data[Character::Fishmen].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::Fishmen].textures = {
        Textures::FishmenToLeft,
        Textures::FishmenToRight,
        Textures::FishmenIdle,
    };
    data[Character::Fishmen].frameSize = sf::Vector2i(42, 44);
    data[Character::Fishmen].isWaterproof = true;
    /*<-------------------------Fishmen------------------------->*/

    /*<-------------------------Orc------------------------->*/
    data[Character::Orc].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 1.2;
    data[Character::Orc].textures = {
        Textures::OrcToLeft,
        Textures::OrcToRight,
        Textures::OrcIdle,
    };
    data[Character::Orc].frameSize = sf::Vector2i(54, 54);
    data[Character::Orc].isWaterproof = true;
    /*<-------------------------Orc------------------------->*/

    /*<-------------------------Wraith------------------------->*/
    data[Character::Wraith].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.8;
    data[Character::Wraith].textures = {
        Textures::WraithToLeft,
        Textures::WraithToRight,
        Textures::WraithIdle,
    };
    data[Character::Wraith].frameSize = sf::Vector2i(44, 50);
    data[Character::Wraith].isWaterproof = true;
    /*<-------------------------Wraith------------------------->*/

    /*<-------------------------WraithPro------------------------->*/
    data[Character::WraithPro].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.9;
    data[Character::WraithPro].textures = {
        Textures::WraithProToLeft,
        Textures::WraithProToRight,
        Textures::WraithProIdle,
    };
    data[Character::WraithPro].frameSize = sf::Vector2i(44, 50);
    data[Character::WraithPro].isWaterproof = true;
    /*<-------------------------WraithPro------------------------->*/

    /*<-------------------------WraithSwamp------------------------->*/
    data[Character::WraithSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.7;
    data[Character::WraithSwamp].textures = {
        Textures::WraithSwampToLeft,
        Textures::WraithSwampToRight,
        Textures::WraithSwampIdle,
    };
    data[Character::WraithSwamp].frameSize = sf::Vector2i(44, 50);
    data[Character::WraithSwamp].isWaterproof = true;
    /*<-------------------------WraithSwamp------------------------->*/

    /*<-------------------------GolemGy------------------------->*/
    data[Character::GolemGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.8;
    data[Character::GolemGy].textures = {
        Textures::GolemGyToLeft,
        Textures::GolemGyToRight,
        Textures::GolemGyIdle,
    };
    data[Character::GolemGy].frameSize = sf::Vector2i(60, 50);
    data[Character::GolemGy].isWaterproof = true;
    /*<-------------------------GolemGy------------------------->*/

    /*<-------------------------Golem------------------------->*/
    data[Character::Golem].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 1.1;
    data[Character::Golem].textures = {
        Textures::GolemToLeft,
        Textures::GolemToRight,
        Textures::GolemIdle,
    };
    data[Character::Golem].frameSize = sf::Vector2i(60, 50);
    data[Character::Golem].isWaterproof = true;
    /*<-------------------------Golem------------------------->*/

    /*<-------------------------GolemSwamp------------------------->*/
    data[Character::GolemSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::GolemSwamp].textures = {
        Textures::GolemSwampToLeft,
        Textures::GolemSwampToRight,
        Textures::GolemSwampIdle,
    };
    data[Character::GolemSwamp].frameSize = sf::Vector2i(60, 50);
    data[Character::GolemSwamp].isWaterproof = true;
    /*<-------------------------GolemSwamp------------------------->*/

    /*<-------------------------SatyrGy------------------------->*/
    data[Character::SatyrGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 1.2;
    data[Character::SatyrGy].textures = {
        Textures::SatyrGyToLeft,
        Textures::SatyrGyToRight,
        Textures::SatyrGyIdle,
    };
    data[Character::SatyrGy].frameSize = sf::Vector2i(48, 48);
    data[Character::SatyrGy].isWaterproof = true;
    /*<-------------------------SatyrGy------------------------->*/

    /*<-------------------------Satyr------------------------->*/
    data[Character::Satyr].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.7;
    data[Character::Satyr].textures = {
        Textures::SatyrToLeft,
        Textures::SatyrToRight,
        Textures::SatyrIdle,
    };
    data[Character::Satyr].frameSize = sf::Vector2i(48, 48);
    data[Character::Satyr].isWaterproof = true;
    /*<-------------------------Satyr------------------------->*/

    /*<-------------------------SatyrSwamp------------------------->*/
    data[Character::SatyrSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::SatyrSwamp].textures = {
        Textures::SatyrSwampToLeft,
        Textures::SatyrSwampToRight,
        Textures::SatyrSwampIdle,
    };
    data[Character::SatyrSwamp].frameSize = sf::Vector2i(48, 48);
    data[Character::SatyrSwamp].isWaterproof = true;
    /*<-------------------------SatyrSwamp------------------------->*/

    /*<-------------------------MinoGy------------------------->*/
    data[Character::MinoGy].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED;
    data[Character::MinoGy].textures = {
        Textures::MinoGyToLeft,
        Textures::MinoGyToRight,
        Textures::MinoGyIdle,
    };
    data[Character::MinoGy].frameSize = sf::Vector2i(58, 56);
    data[Character::MinoGy].isWaterproof = true;
    /*<-------------------------MinoGy------------------------->*/

    /*<-------------------------Mino------------------------->*/
    data[Character::Mino].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 1.1;
    data[Character::Mino].textures = {
        Textures::MinoToLeft,
        Textures::MinoToRight,
        Textures::MinoIdle,
    };
    data[Character::Mino].frameSize = sf::Vector2i(58, 56);
    data[Character::Mino].isWaterproof = true;
    /*<-------------------------Mino------------------------->*/

    /*<-------------------------MinoSwamp------------------------->*/
    data[Character::MinoSwamp].normalSpeed = DEFAULT_GROUND_ENEMY_SPEED * 0.8;
    data[Character::MinoSwamp].textures = {
        Textures::MinoSwampToLeft,
        Textures::MinoSwampToRight,
        Textures::MinoSwampIdle,
    };
    data[Character::MinoSwamp].frameSize = sf::Vector2i(58, 56);
    data[Character::MinoSwamp].isWaterproof = true;
    /*<-------------------------MinoSwamp------------------------->*/

    // Skin data
    /*<-------------------------Archer------------------------->*/
    data[Character::Archer].normalSpeed = DEFAULT_PLAYER_SPEED;
    data[Character::Archer].textures = {
        Textures::ArcherToLeft,
        Textures::ArcherToRight,
        Textures::ArcherIdle,
        Textures::ArcherDead,
    };
    data[Character::Archer].frameSize = sf::Vector2i(42, 38);
    data[Character::Archer].isWaterproof = false;
    /*<-------------------------Archer------------------------->*/

    /*<-------------------------Enchantress------------------------->*/
    data[Character::Enchantress].normalSpeed = DEFAULT_PLAYER_SPEED * 0.7;
    data[Character::Enchantress].textures = {
        Textures::EnchantressToLeft,
        Textures::EnchantressToRight,
        Textures::EnchantressIdle,
        Textures::EnchantressDead,
    };
    data[Character::Enchantress].frameSize = sf::Vector2i(42, 38);
    data[Character::Enchantress].isWaterproof = true;
    /*<-------------------------Enchantress------------------------->*/

    /*<-------------------------Knight------------------------->*/
    data[Character::Knight].normalSpeed = DEFAULT_PLAYER_SPEED;
    data[Character::Knight].textures = {
        Textures::KnightToLeft,
        Textures::KnightToRight,
        Textures::KnightIdle,
        Textures::KnightDead,
    };
    data[Character::Knight].frameSize = sf::Vector2i(42, 38);
    data[Character::Knight].isWaterproof = false;
    /*<-------------------------Knight------------------------->*/

    /*<-------------------------Musketeer------------------------->*/
    data[Character::Musketeer].normalSpeed = DEFAULT_PLAYER_SPEED * 1.2;
    data[Character::Musketeer].textures = {
        Textures::MusketeerToLeft,
        Textures::MusketeerToRight,
        Textures::MusketeerIdle,
        Textures::MusketeerDead,
    };
    data[Character::Musketeer].frameSize = sf::Vector2i(42, 38);
    data[Character::Musketeer].isWaterproof = false;
    /*<-------------------------Musketeer------------------------->*/

    /*<-------------------------Swordsman------------------------->*/
    data[Character::Swordsman].normalSpeed = DEFAULT_PLAYER_SPEED * 1.1;
    data[Character::Swordsman].textures = {
        Textures::SwordsmanToLeft,
        Textures::SwordsmanToRight,
        Textures::SwordsmanIdle,
        Textures::SwordsmanDead,
    };
    data[Character::Swordsman].frameSize = sf::Vector2i(42, 38);
    data[Character::Swordsman].isWaterproof = false;
    /*<-------------------------Swordsman------------------------->*/

    /*<-------------------------Wizard------------------------->*/
    data[Character::Wizard].normalSpeed = DEFAULT_PLAYER_SPEED * 0.8;
    data[Character::Wizard].textures = {
        Textures::WizardToLeft,
        Textures::WizardToRight,
        Textures::WizardIdle,
        Textures::WizardDead,
    };
    data[Character::Wizard].frameSize = sf::Vector2i(42, 38);
    data[Character::Wizard].isWaterproof = true;
    /*<-------------------------Wizard------------------------->*/

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

std::vector<TrafficLightData> initializeTrafficLightData() {
    std::vector<TrafficLightData> data(TrafficLight::Type::TypeCount);

    for (int i = 0; i < TrafficLight::Type::TypeCount; ++i) {
        data[i].texture =
            static_cast<Textures::ID>(Textures::Field_TrafficLight + i);
        data[i].textureRect = sf::IntRect(0, 0, 48, 64);
    }

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

std::vector<ObjectFactoryData> initializeObjectFactoryData() {
    // Grass, Dirt and Soil share the same object factory data
    std::vector<ObjectFactoryData> data(ObjectFactoryData::TypeCount);

    // Common air spawn types
    // River is the same as "None" type
    for (int i = 0; i < ObjectFactoryData::River; ++i) {
        data[i].airSpawnTypes = {
            Character::Type::BeeBoss,
            Character::Type::BombBat,
            Character::Type::Bird,
        };
    }

    // Dirt, Grass, Soil
    data[ObjectFactoryData::Field].groundSpawnTypes = {
        Character::Type::Dog, Character::Type::Wraith, Character::Type::Golem,
        Character::Type::Satyr, Character::Type::Mino
    };
    data[ObjectFactoryData::Field].obstacleSpawnTypes = {
        Obstacle::Field_Bush, Obstacle::Field_Stone6, Obstacle::Field_Tent,
        Obstacle::Field_Tree1
    };

    // Graveyard
    data[ObjectFactoryData::Graveyard].groundSpawnTypes = {
        Character::Type::WraithPro,
        Character::Type::GolemGy,
        Character::Type::SatyrGy,
        Character::Type::MinoGy,
    };
    data[ObjectFactoryData::Graveyard].obstacleSpawnTypes = {
        Obstacle::Graveyard_House1, Obstacle::Graveyard_Statue8,
        Obstacle::Graveyard_Tree2
    };

    // Swamp
    data[ObjectFactoryData::Swamp].groundSpawnTypes = {
        Character::Type::Orc,         Character::Type::Crocodile,
        Character::Type::WraithSwamp, Character::Type::GolemSwamp,
        Character::Type::SatyrSwamp,  Character::Type::MinoSwamp,
    };
    data[ObjectFactoryData::Swamp].obstacleSpawnTypes = {
        Obstacle::Swamp_House1, Obstacle::Swamp_Tree2, Obstacle::Swamp_Well1
    };

    return data;
}
