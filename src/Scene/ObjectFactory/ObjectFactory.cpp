#include "ObjectFactory.hpp"

#include <cstdlib>

#include "Utility.hpp"

ObjectFactory::ObjectFactory(const TextureHolder& textures, LaneType laneType)
    : mTextures(&textures), mLaneType(laneType) {
    mAirEnemies = {
        Character::Type::Bee, Character::Type::Bird, Character::Type::BeeBoss,
        Character::Type::BombBat
    };
    switch (mLaneType) {
        case LaneType::Dirt:
        case LaneType::Grass:
        case LaneType::Soil: {
            mObstacles = {Obstacle::bush1, Obstacle::stone1, Obstacle::tree1};
            mGroundEnemies = {
                Character::Type::Dog, Character::Type::Rabbit,
                Character::Type::Sheep, Character::Type::Zombie
            };

            break;
        }

        case LaneType::Graveyard: {
            mObstacles = {
                Obstacle::gy_tree1, Obstacle::statue1, Obstacle::statue2
            };
            mGroundEnemies = {
                Character::Type::Orc, Character::Type::Dog,
                Character::Type::Fishmen, Character::Type::Zombie
            };

            break;
        }

        case LaneType::Swamp: {
            mObstacles = {Obstacle::stone1, Obstacle::stone1, Obstacle::well};
            mGroundEnemies = {
                Character::Type::Turtle, Character::Type::Frog,
                Character::Type::Fishmen, Character::Type::Zombie
            };

            break;
        }

        default:
            break;
    }
}

// std::unique_ptr<SceneNode> ObjectFactory::createObject(ObjectType type) {
//     std::unique_ptr<SceneNode> object;
//     switch (type) {
//         case ObjectType::TAirEnemy: {
//             object = createAirEnemy();
//         }
//         case ObjectType::TGroundEnemy: {
//             object = createGroundEnemy();
//         }
//         case ObjectType::TObstacle: {
//             object = createObstacle();
//         }
//         case ObjectType::TTrafficLight: {
//             object = createTrafficLight();
//         }
//     }
//     centerOrigin(*object);
//     return object;
// }

std::unique_ptr<Character> ObjectFactory::createAirEnemy() {
    unsigned int objectType = rand() % mAirEnemies.size();
    return std::make_unique<Character>(
        static_cast<Character::Type>(objectType), *mTextures
    );
}

std::unique_ptr<Character> ObjectFactory::createGroundEnemy() {
    unsigned int objectType = rand() % mGroundEnemies.size();
    return std::make_unique<Character>(
        static_cast<Character::Type>(objectType), *mTextures
    );
}

std::unique_ptr<Obstacle> ObjectFactory::createObstacle() {
    unsigned int objectType = rand() % mObstacles.size();
    return std::make_unique<Obstacle>(
        static_cast<Obstacle::Type>(objectType), *mTextures
    );
}

std::unique_ptr<TrafficLight> ObjectFactory::createTrafficLight() {
    TrafficLight::Type trafficLightType;
    switch (mLaneType) {
        case LaneType::Dirt:
        case LaneType::Grass:
        case LaneType::Soil: {
            trafficLightType = TrafficLight::Type::Field;
            break;
        }
        case LaneType::Graveyard: {
            trafficLightType = TrafficLight::Type::Graveyard;
            break;
        }
        case LaneType::Swamp: {
            trafficLightType = TrafficLight::Type::Swamp;
            break;
        }
    }

    return std::make_unique<TrafficLight>(trafficLightType, *mTextures);
}