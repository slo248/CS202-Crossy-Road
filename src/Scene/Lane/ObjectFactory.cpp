#include "ObjectFactory.hpp"

#include <cstdlib>

#include "DataTables.hpp"
#include "Utility.hpp"

namespace {
const std::vector<ObjectFactoryData> Table = initializeObjectFactoryData();
}

ObjectFactory::ObjectFactory(
    const TextureHolder& textures, LaneType laneType, float levelScale
)
    : mTextures(&textures), mLaneType(laneType), mLevelScale(levelScale) {
    int type = ObjectFactoryData::River;
    switch (mLaneType) {
        case LaneType::Dirt:
        case LaneType::Grass:
        case LaneType::Soil: {
            type = ObjectFactoryData::Field;
            break;
        }

        case LaneType::Graveyard: {
            type = ObjectFactoryData::Graveyard;
            break;
        }

        case LaneType::Swamp: {
            type = ObjectFactoryData::Swamp;
            break;
        }
    }

    mAirSpawnTypes = &Table[type].airSpawnTypes;
    mGroundSpawnTypes = &Table[type].groundSpawnTypes;
    mObstacleSpawnTypes = &Table[type].obstacleSpawnTypes;
}

std::unique_ptr<Character> ObjectFactory::createAirEnemy() {
    unsigned int objectType = rand() % mAirSpawnTypes->size();
    return std::make_unique<Character>(
        (*mAirSpawnTypes)[objectType], *mTextures, mLevelScale
    );
}

std::unique_ptr<Character> ObjectFactory::createGroundEnemy() {
    unsigned int objectType = rand() % mGroundSpawnTypes->size();
    return std::make_unique<Character>(
        (*mGroundSpawnTypes)[objectType], *mTextures, mLevelScale
    );
}

std::unique_ptr<Obstacle> ObjectFactory::createObstacle() {
    unsigned int objectType = rand() % mObstacleSpawnTypes->size();
    return std::make_unique<Obstacle>(
        (*mObstacleSpawnTypes)[objectType], *mTextures, mLevelScale
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
