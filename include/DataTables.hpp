#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "ResourceIdentifiers.hpp"

class Animal;
class Enemy;
class Obstacle;
class Lane;
class TraffictLight;

struct Direction {
    Direction(float angle, float distance) : angle(angle), distance(distance) {}

    float angle;
    float distance;
};

struct AnimalData {
    float speed;
    Textures::ID texture;
    sf::IntRect textureRect;
};

struct EnemyData {
    float speed;
    Textures::ID texture;
    sf::IntRect textureRect;
};

struct ObstacleData {
    float speed;
    Textures::ID texture;
    sf::IntRect textureRect;
    bool isBlockingPlayer;
    bool isHavingMovement;
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

std::vector<AnimalData> initializeAnimalData();
std::vector<EnemyData> initializeEnemyData();
std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();
std::vector<TrafficLightData> initializeTrafficLightData();

#endif  // DATATABLES_HPP
