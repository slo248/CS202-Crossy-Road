#ifndef LANE_HPP
#define LANE_HPP

#include <SFML/System/Clock.hpp>

#include "ObjectFactory.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "TrafficLight.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;
    enum SpawnSide { Left, None, Right };

    Lane(
        LaneType type, const TextureHolder& textures, Ptr childLane = nullptr,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    Lane* getChildLane();
    bool checkMovablePlayer(Character* player, Character::Direction direction);

   private:
    void spawnObstacles();
    void spawnTrafficLight();
    void spawnGroundEnemy();
    void spawnAirEnemy();
    void spawnLog();
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

Lane::Ptr createMultipleLanes(const TextureHolder& textures, int laneNumber);

float slotToPosition(int slot);

#endif  // LANE_HPP
