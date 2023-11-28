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

void Movement::setup(
    sf::Vector2f start, sf::Vector2f end, sf::Vector2f speed,
    std::function<float(float)> motion
) {
    mStart = start;
    mEnd = end;
    mDuration = sf::seconds(
        sqrt(pow(mEnd.x - mStart.x, 2) + pow(mEnd.y - mStart.y, 2)) /
        sqrt(pow(speed.x, 2) + pow(speed.y, 2))
    );
    mElapsed = sf::Time::Zero;
    mMotion = motion;
}

void Movement::update(sf::Time dt) {
    if (mMotion == nullptr) return;
    mElapsed += dt;
    if (mElapsed > mDuration) {
        mObj->setPosition(mEnd);
        return;
    }
    float t = mMotion(mElapsed.asSeconds() / mDuration.asSeconds());
    mObj->setPosition(
        mStart.x + (mEnd.x - mStart.x) * t, mStart.y + (mEnd.y - mStart.y) * t
    );
}
