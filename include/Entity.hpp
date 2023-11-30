#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
   public:
    Entity(sf::Vector2f normalVelocity = {0, 0});
    enum Direction { MoveToLeft, MoveToRight, StandStill };

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);
    void setScaleNormalVelocity(float times);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);
    sf::Vector2f getVelocity();

   protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

   private:
    sf::Vector2f mVelocity;
    const sf::Vector2f mNormalVelocity;
};

#endif  // ENTITY_HPP
