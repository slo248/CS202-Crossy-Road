#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode {
   public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float x, float y);
    sf::Vector2f getVelocity();

    int getDirectionIndex();
    void setDirectionIndex(int directionIndex);

   protected:
    virtual void updateCurrent(sf::Time dt);

   private:
    sf::Vector2f mVelocity;
    int mDirectionIndex;
};

#endif  // ENTITY_HPP
