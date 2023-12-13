#include "ObjectFactory.hpp"

#include <cstdlib>

#include "Utility.hpp"

ObjectFactory::ObjectFactory(
    const TextureHolder& textures, LaneType laneType, float levelScale
)
    : mTextures(&textures), mLaneType(laneType), mLevelScale(levelScale) {
    mAirEnemies = {
        Character::Type::Bee, Character::Type::Bird, Character::Type::BeeBoss,
        Character::Type::BombBat
    };

    switch (mLaneType) {
        case LaneType::Dirt:
        case LaneType::Grass:
        case LaneType::Soil: {
            mObstacles = {
                Obstacle::Field_Bush,
                Obstacle::Field_Stone6,
                Obstacle::Field_Tent,
                Obstacle::Field_Tree1,
            };
            mGroundEnemies = {
                Character::Type::Dog,       Character::Type::Rabbit,
                Character::Type::Sheep,     Character::Type::Zombie,
                Character::Type::Crocodile, Character::Type::Wraith,
            };

            break;
        }

        case LaneType::Graveyard: {
            mObstacles = {
                Obstacle::Graveyard_House1, Obstacle::Graveyard_Statue8,
                Obstacle::Graveyard_Tree2
            };
            mGroundEnemies = {
                Character::Type::Orc,       Character::Type::Dog,
                Character::Type::Fishmen,   Character::Type::Zombie,
                Character::Type::Crocodile, Character::Type::Wraith,
            };

            break;
        }

        case LaneType::Swamp: {
            mObstacles = {
                Obstacle::Swamp_House1, Obstacle::Swamp_Tree2,
                Obstacle::Swamp_Well1
            };
            mGroundEnemies = {
                Character::Type::Turtle,    Character::Type::Frog,
                Character::Type::Fishmen,   Character::Type::Zombie,
                Character::Type::Crocodile, Character::Type::Wraith,
            };

            break;
        }

        default:
            break;
    }
}

std::unique_ptr<Character> ObjectFactory::createAirEnemy() {
    unsigned int objectType = rand() % mAirEnemies.size();
    return std::make_unique<Character>(
        static_cast<Character::Type>(mAirEnemies[objectType]), *mTextures,
        mLevelScale
    );
}

std::unique_ptr<Character> ObjectFactory::createGroundEnemy() {
    unsigned int objectType = rand() % mGroundEnemies.size();
    return std::make_unique<Character>(
        static_cast<Character::Type>(mGroundEnemies[objectType]), *mTextures,
        mLevelScale
    );
}

std::unique_ptr<Obstacle> ObjectFactory::createObstacle() {
    unsigned int objectType = rand() % mObstacles.size();
    return std::make_unique<Obstacle>(
        static_cast<Obstacle::Type>(mObstacles[objectType]), *mTextures,
        mLevelScale
    );
}

std::unique_ptr<TrafficLight> ObjectFactory::createTrafficLight() {
    TrafficLight::Type trafficLightType = TrafficLight::Type::Field;
    switch (mLaneType) {
        case LaneType::Graveyard: {
            trafficLightType = TrafficLight::Type::Graveyard;
            break;
        }
        case LaneType::Swamp: {
            trafficLightType = TrafficLight::Type::Swamp;
            break;
        }

        default: {
            break;
        }
    }

    return std::make_unique<TrafficLight>(trafficLightType, *mTextures);
}

std::unique_ptr<Obstacle> ObjectFactory::createLog() {
    return std::make_unique<Obstacle>(
        Obstacle::Type::River_Log1, *mTextures, mLevelScale
    );
}

SceneNode::Ptr ObjectFactory::createObject(
    std::istream& in, Category::Type category
) {
    int type;
    in >> type;
    SceneNode::Ptr object = nullptr;
    switch (category) {
        case Category::Type::Enemy: {
            return std::make_unique<Character>(
                in, static_cast<Character::Type>(type), *mTextures, mLevelScale
            );
        }

        case Category::Type::Decoration:
        case Category::Type::Obstacle: {
            return std::make_unique<Obstacle>(
                in, static_cast<Obstacle::Type>(type), *mTextures, mLevelScale
            );
        }

        case Category::Type::TrafficLight: {
            return std::make_unique<TrafficLight>(
                in, static_cast<TrafficLight::Type>(type), *mTextures
            );
        }
    }
    return object;
}
