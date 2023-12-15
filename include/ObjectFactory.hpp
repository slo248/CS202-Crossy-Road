#ifndef OBJECT_FACTORY_HPP
#define OBJECT_FACTORY_HPP

#include "Character.hpp"
#include "Config.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "TrafficLight.hpp"

enum LaneType { Dirt, Grass, Graveyard, Soil, Swamp, River, TypeCount };

class ObjectFactory {
   public:
    explicit ObjectFactory(
        const TextureHolder& textures, LaneType laneType,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );

    // Normal object creation
    std::unique_ptr<Character> createAirEnemy();
    std::unique_ptr<Character> createGroundEnemy();
    std::unique_ptr<Obstacle> createObstacle();
    std::unique_ptr<TrafficLight> createTrafficLight();
    std::unique_ptr<Obstacle> createLog();

    // Object creation from file
    SceneNode::Ptr createObject(std::istream& in, Category::Type type);
    /*
    What we may actually need
    Movealbe(Enemy, Ally),
    UnMoveable(Obstacle, Decoration)
    TrafficLight
    good classification leads to good design
    */

   private:
    const TextureHolder* mTextures;
    LaneType mLaneType;
    std::vector<Character::Type> mAirEnemies;
    std::vector<Character::Type> mGroundEnemies;
    std::vector<Obstacle::Type> mObstacles;
    float mLevelScale;
};

#endif  // OBJECT_FACTORY_HPP
