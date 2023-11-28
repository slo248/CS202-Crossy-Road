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

    void setup(
        sf::Vector2f start, sf::Vector2f end, sf::Vector2f speed,
        std::function<float(float)> motion = Motion::Linear()
    );

    void update(sf::Time dt);

   private:
    Entity* mObj;
    sf::Vector2f mStart, mEnd;
    sf::Time mDuration, mElapsed;
    std::function<float(float)> mMotion;
};

#endif  // MOVEMENT_HPP
