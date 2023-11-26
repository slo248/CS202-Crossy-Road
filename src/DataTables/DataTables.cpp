#include "DataTables.hpp"

#include "Character.hpp"
#include "Lane.hpp"
#include "Obstacle.hpp"
#include "TrafficLight.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CharacterData> initializeCharacterData() {
    std::vector<CharacterData> data(Character::TypeCount);

    for (int i = 0; i < Character::TypeCount; ++i) {
        data[i].speed = 200.f;
        data[i].texture = static_cast<Textures::ID>(Textures::Bee + i);
        data[i].textureRect = DEFAULT_CELL;
    }

    return data;
}

std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);

    for (int i = 0; i < Obstacle::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::f_fence + i);
        data[i].textureRect = DEFAULT_CELL;
        data[i].isBlockingPlayer = true;
    }

    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data(LaneType::TypeCount);

    for (int i = 0; i < LaneType::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::River + i);
        data[i].textureRect = DEFAULT_LANE;
        data[i].spawnInterval = DEFAULT_SPAWN_INTERVAL;
    }

    return data;
}

std::vector<TrafficLightData> initializeTrafficLightData() {
    std::vector<TrafficLightData> data(TrafficLight::Type::TypeCount);

    for (int i = 0; i < TrafficLight::Type::TypeCount; ++i) {
        data[i].texture =
            static_cast<Textures::ID>(Textures::FieldTrafficLight + i);
        data[i].textureRect = DEFAULT_CELL;
    }

    return data;
}
