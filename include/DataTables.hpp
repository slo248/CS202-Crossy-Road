#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "ResourceIdentifiers.hpp"

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
    float speed;
    Textures::ID texture;
    sf::IntRect textureRect;
    bool isBlockingPlayer;
};

struct LaneData {
    Textures::ID texture;
    sf::IntRect textureRect;
    bool isHavingMovement;
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
