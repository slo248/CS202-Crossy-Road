#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
   public:
    enum Direction { MoveToLeft, MoveToRight, StandStill };

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);
    sf::Vector2f getVelocity();

    unsigned int getDirection();
    void setDirectionIndex(Direction direction);

   protected:
    virtual void updateCurrent(sf::Time dt);

   private:
    sf::Vector2f mVelocity;
    Direction mDirection;
};

#endif  // ENTITY_HPP
