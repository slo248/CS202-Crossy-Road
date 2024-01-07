#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
   public:
    enum Direction { MoveToLeft, MoveToRight, StandStill };

    Entity(sf::Vector2f normalVelocity = {0, 0});

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);
    void setScaleNormalVelocity(float times);
    void setTemporaryNormalVelocity(float temporaryFactor);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

    sf::Vector2f getVelocity() const;
    sf::Vector2f getNormalVelocity() const;
    float getTemporaryFactor();

   protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

   private:
    sf::Vector2f mVelocity;              // save
    const sf::Vector2f mNormalVelocity;  // save
    float mTemporaryFactor;
};

#endif  // ENTITY_HPP
