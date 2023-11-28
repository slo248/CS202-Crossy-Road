#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

#include "Motion.hpp"

class Entity;

class Movement {
   public:
    Movement(Entity* obj);

   private:
    Entity* mObj;
    sf::Vector2f mStart, mEnd;
    sf::Time mDuration, mElapsed;
    std::function<float(float)> mMotion;
};

#endif  // MOVEMENT_HPP
