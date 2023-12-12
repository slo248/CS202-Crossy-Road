#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "Config.hpp"
#include "ResourceIdentifiers.hpp"

class Character;
class Obstacle;
class Lane;
class TraffictLight;

struct CharacterData {
    enum Direction { ToLeft, ToRight, Idle, ToUpper, ToLower };
    float normalSpeed;
    std::vector<Textures::ID> textures;
    sf::Vector2i frameSize;
    size_t numFrames;
};

struct ObstacleData {
    Textures::ID texture;
    sf::IntRect textureRect;
    float normalSpeed;
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
