#ifndef LANE_HPP
#define LANE_HPP

#include <SFML/System/Clock.hpp>

#include "ObjectFactory.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "TrafficLight.hpp"

class Lane : public SceneNode {
   public:
    enum SpawnSide { Left, None, Right };

    Lane(LaneType type, const TextureHolder& textures, Ptr childLane = nullptr);

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    Lane* getChildLane();

   private:
    void spawnObstacles();
    void spawnTrafficLight();
    void spawnGroundEnemy();
    void spawnAirEnemy();
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void updateMovementPattern(sf::Time dt);

   private:
    LaneType mType;
    SpawnSide mSpawnSide;
    sf::Sprite mSprite;
    sf::Time mSpawnInterval;
    Lane* mChildLane;
    TrafficLight* mTrafficLight;
    std::unique_ptr<ObjectFactory> mObjectFactory;
};

float slotToPosition(int slot);

#endif  // LANE_HPP
