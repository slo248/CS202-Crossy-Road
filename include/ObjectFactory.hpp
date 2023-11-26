#ifndef OBJECT_FACTORY_HPP
#define OBJECT_FACTORY_HPP

#include "Character.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "TrafficLight.hpp"

enum LaneType { River, Dirt, Grass, Graveyard, Soil, Swamp, TypeCount };

class ObjectFactory {
   public:
    explicit ObjectFactory(const TextureHolder& textures, LaneType laneType);

    // std::unique_ptr<SceneNode> createObject(ObjectType type);
    std::unique_ptr<Character> createAirEnemy();
    std::unique_ptr<Character> createGroundEnemy();
    std::unique_ptr<Obstacle> createObstacle();
    std::unique_ptr<TrafficLight> createTrafficLight();

   private:
    const TextureHolder* mTextures;
    LaneType mLaneType;
    std::vector<Character::Type> mAirEnemies;
    std::vector<Character::Type> mGroundEnemies;
    std::vector<Obstacle::Type> mObstacles;
};

#endif  // OBJECT_FACTORY_HPP
