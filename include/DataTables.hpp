#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "ResourceIdentifiers.hpp"

#define DEFAULT_CELL_LENGTH 64
#define DEFAULT_CELL sf::IntRect(0, 0, DEFAULT_CELL_LENGTH, DEFAULT_CELL_LENGTH)
#define DEFAULT_LANE \
    sf::IntRect(0, 0, DEFAULT_CELL_LENGTH * 12, DEFAULT_CELL_LENGTH)
#define DEFAULT_SPAWN_INTERVAL sf::seconds(0.5)
#define DEFAULT_LANE_LENGTH 12

// #define MODE_EASY 1.0
// #define MODE_MEDIUM 1.1
// #define MODE_HARD 1.2

class Character;
class Obstacle;
class Lane;
class TraffictLight;

struct Direction {
    Direction(float angle, float distance) : angle(angle), distance(distance) {}

    float angle;
    float distance;
};

struct CharacterData {
    float speed;
    Textures::ID texture;
    sf::IntRect textureRect;
};

struct ObstacleData {
    Textures::ID texture;
    sf::IntRect textureRect;
    bool isBlockingPlayer;
};

struct LaneData {
    Textures::ID texture;
    sf::IntRect textureRect;
    sf::Time spawnInterval;
};

struct TrafficLightData {
    Textures::ID texture;
    sf::IntRect textureRect;
};

std::vector<CharacterData> initializeCharacterData();
std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();
std::vector<TrafficLightData> initializeTrafficLightData();

#endif  // DATATABLES_HPP
