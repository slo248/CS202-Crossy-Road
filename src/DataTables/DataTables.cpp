#include "DataTables.hpp"

#include "Animal.hpp"
#include "Character.hpp"
#include "Lane.hpp"
#include "Obstacle.hpp"
#include "PlayerSkin.hpp"
#include "TrafficLight.hpp"

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

#define DEFAULT_CELL sf::IntRect(0, 0, 96, 96)
#define DEFAULT_LANE sf::IntRect(0, 0, 960, 1024)

std::vector<CharacterData> initializeCharacterData() {
    std::vector<CharacterData> data(Character::TypeCount);

    for (int i = 0; i < Character::TypeCount; ++i) {
        data[i].speed = 200.f;
        data[i].texture = static_cast<Textures::ID>(Textures::bee_boss + i);
        data[i].textureRect = sf::IntRect(0, 0, 48, 64);
    }

    return data;
}

std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);

    for (int i = 0; i < Obstacle::TypeCount; ++i) {
        data[i].speed = 200.f;
        data[i].texture = static_cast<Textures::ID>(Textures::f_fence + i);
        data[i].textureRect = DEFAULT_CELL;
        data[i].isBlockingPlayer = true;
    }

    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data(Lane::TypeCount);

    for (int i = 0; i < Lane::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::river + i);
        data[i].textureRect = DEFAULT_LANE;
    }

    return data;
}

std::vector<TrafficLightData> initializeTrafficLightData() {
    std::vector<TrafficLightData> data(TrafficLight::TypeCount);

    for (int i = 0; i < TrafficLight::TypeCount; ++i) {
        data[i].texture = static_cast<Textures::ID>(Textures::f_traffic + i);
        data[i].textureRect = DEFAULT_CELL;
    }

    return data;
}
