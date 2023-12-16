#ifndef LANE_HPP
#define LANE_HPP

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "ObjectFactory.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "TrafficLight.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;
    enum SpawnSide { Left, Right, None };

    Lane(
        LaneType type, const TextureHolder& textures, bool isBufferLane,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    // levelScale should not be passed to the constructor, it should be global
    explicit Lane(
        std::istream& in, LaneType type, const TextureHolder& textures,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    ~Lane();

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Lane* getParentLane();
    Lane* getChildLane();
    LaneType getType();
    SpawnSide getSpawnSide();
    float getRandomFactor() const;

    sf::Vector2f checkMoveablePlayer(
        Character* player, Character::Direction direction
    );
    bool isCollidedWithPlayer(Character* player);
    void attachChild(SceneNode::Ptr child) override;

   private:
    Lane(LaneType type, const TextureHolder& textures, float levelScale);

    void spawnObstacles(bool isBufferLane = false);
    void spawnTrafficLight();
    void spawnGroundEnemy();
    void spawnAirEnemy();
    void spawnLog();

    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;

    virtual void saveCurrent(std::ostream& out) const override;
    virtual void saveChildren(std::ostream& out) const override;

    virtual void loadCurrent(std::istream& in) override;
    virtual void loadChildren(std::istream& in, const TextureHolder& textures)
        override;

   private:
    LaneType mType;                                 // Save
    SpawnSide mSpawnSide;                           // Save
    sf::Sprite mSprite;                             // Type-dependent
    sf::Time mSpawnInterval;                        // Type-dependent
    sf::Time mElapsedTime;                          // Type-dependent
    Lane* mChildLane;                               // Saved independently
    TrafficLight* mTrafficLight;                    // Saved independently
    std::unique_ptr<ObjectFactory> mObjectFactory;  // Type-dependent
    float mRandomFactor;                            // Save
};

void createMultipleLanes(
    const TextureHolder& textures, int numberOfLanes, Lane::Ptr& topLane,
    Lane*& bottomLane, bool isBuffer = false,
    float levelScale = LEVEL_ONE_COEFFICIENT

);

#endif  // LANE_HPP
