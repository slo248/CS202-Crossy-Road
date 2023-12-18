#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <functional>
#include <vector>

#include "Character.hpp"
#include "Config.hpp"
#include "Lane.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "TrafficLight.hpp"

// class Character;
// class Obstacle;
// class Lane;
// class TraffictLight;

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

struct TrafficLightData {
    Textures::ID texture;
    sf::IntRect textureRect;
};

struct ObjectFactoryData {
    enum Type { Field, Graveyard, Swamp, River, TypeCount };
    std::vector<Character::Type> airSpawnTypes;
    std::vector<Character::Type> groundSpawnTypes;
    std::vector<Obstacle::Type> obstacleSpawnTypes;
};

struct LaneData {
    Textures::ID texture;
    sf::IntRect textureRect;
    sf::Time spawnInterval;
};

std::vector<CharacterData> initializeCharacterData();
std::vector<ObstacleData> initializeObstacleData();
std::vector<TrafficLightData> initializeTrafficLightData();
std::vector<LaneData> initializeLaneData();
std::vector<ObjectFactoryData> initializeObjectFactoryData();

#endif  // DATATABLES_HPP
