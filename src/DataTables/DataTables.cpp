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
    for (int i = 0; i < Character::Archer; ++i) {
        data[i].normalSpeed = 200.f;
        int tmp = 4 * i;
        data[i].textures = {
            static_cast<Textures::ID>(Textures::BeeToLeft + tmp),
            static_cast<Textures::ID>(Textures::BeeToRight + tmp),
            static_cast<Textures::ID>(Textures::BeeToLeft + tmp),
            static_cast<Textures::ID>(Textures::BeeToRight + tmp),
        };
        data[i].frameSize = DEFAULT_CELL_RECT.getSize();
        data[i].numFrames = 4;
    }

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

    data[Obstacle::Type::River_Log1].normalSpeed = 70.f;
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
