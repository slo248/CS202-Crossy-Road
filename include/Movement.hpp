#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

class Entity;

class Movement {
   public:
    Movement(Entity* obj);

    void setup(sf::Vector2f dst, std::function<float(float)> motion);

    void update(sf::Time dt);
    bool isFinished() const;

   private:
    Entity* mObj;
    sf::Vector2f mStart, mEnd;
    sf::Time mDuration, mElapsed;
    std::function<float(float)> mMotion;
};

#endif  // MOVEMENT_HPP
