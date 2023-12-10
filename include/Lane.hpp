#ifndef LANE_HPP
#define LANE_HPP

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "ObjectFactory.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "TrafficLight.hpp"

// class LaneTypeHolder {
//    public:
//     LaneTypeHolder(LaneType type) : mType(type) {}
//     LaneType getType() const { return mType; }
//     ~LaneTypeHolder() { std::cout << "LaneTypeHolder destroyed\n"; }

//    private:
//     const LaneType mType;
// };

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;
    enum SpawnSide { Left, Right, None };

    Lane(
        LaneType type, const TextureHolder& textures, bool isBufferLane = false,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    ~Lane();

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Lane* getChildLane();
    sf::Vector2f checkMoveablePlayer(
        Character* player, Character::Direction direction
    );
    bool isCollidedWithPlayer(Character* player);
    float getRandomFactor() const;
    void attachChild(SceneNode::Ptr child) override;

   private:
    void spawnObstacles(bool isBufferLane = false);
    void spawnTrafficLight();
    void spawnGroundEnemy();
    void spawnAirEnemy();
    void spawnLog();
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void updateMovementPattern(sf::Time dt);

   private:
    LaneType mType;
    // const LaneTypeHolder* const mTypeHolder;
    SpawnSide mSpawnSide;
    sf::Sprite mSprite;
    sf::Time mSpawnInterval;
    Lane* mChildLane;
    TrafficLight* mTrafficLight;
    std::unique_ptr<ObjectFactory> mObjectFactory;
    float mRandomFactor;
};

void createMultipleLanes(
    const TextureHolder& textures, int numberOfLanes, Lane::Ptr& topLane,
    Lane*& botLane, bool isBuffer = false,
    float levelScale = LEVEL_ONE_COEFFICIENT

);

float slotToPosition(int slot);

#endif  // LANE_HPP
