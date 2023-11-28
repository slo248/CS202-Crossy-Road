#include "Movement.hpp"

#include <stdexcept>

#include "Entity.hpp"

Movement::Movement(Entity* obj) : mObj(obj) {
    if (mObj == nullptr)
        throw std::runtime_error("Entity is null in Movement constructor");
    mStart = mEnd = mObj->getPosition();
    mElapsed = mDuration = sf::Time::Zero;
    mMotion = nullptr;
}
