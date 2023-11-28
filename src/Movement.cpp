#include "Movement.hpp"

#include <cmath>
#include <stdexcept>

#include "Entity.hpp"

Movement::Movement(Entity* obj) : mObj(obj) {
    if (mObj == nullptr)
        throw std::runtime_error("Entity is null in Movement constructor");
    mStart = mEnd = mObj->getPosition();
    mElapsed = mDuration = sf::Time::Zero;
    mMotion = nullptr;
}

void Movement::setup(sf::Vector2f dst, std::function<float(float)> motion) {
    mEnd = dst;
    mMotion = motion;

    mStart = mObj->getPosition();
    sf::Vector2f vel = mObj->getVelocity();
    mDuration = sf::seconds(
        sqrt(pow(mEnd.x - mStart.x, 2) + pow(mEnd.y - mStart.y, 2)) /
        sqrt(pow(vel.x, 2) + pow(vel.y, 2))
    );
    mElapsed = sf::Time::Zero;
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
