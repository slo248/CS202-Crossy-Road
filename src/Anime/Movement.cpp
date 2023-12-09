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
    if (dst == mEnd) return;
    mEnd = dst;
    mMotion = motion;

    mStart = mObj->getPosition();
    sf::Vector2f vel = mObj->getVelocity();
    mDuration = sf::seconds(
        sqrt(
            (mEnd.x - mStart.x) * (mEnd.x - mStart.x) +
            (mEnd.y - mStart.y) * (mEnd.y - mStart.y)
        ) /
        sqrt(vel.x * vel.x + vel.y * vel.y)
    );
    mElapsed = sf::Time::Zero;
}

void Movement::update(sf::Time dt) {
    if (mMotion == nullptr) return;
    mElapsed += dt;
    if (mElapsed > mDuration) {
        mObj->setPosition(mEnd);
        mObj->setVelocity(sf::Vector2f(0.f, 0.f));
        return;
    }
    float t = mMotion(mElapsed.asSeconds() / mDuration.asSeconds());
    mObj->setPosition(mStart + (mEnd - mStart) * t);
    mObj->setVelocity((mEnd - mStart) / mDuration.asSeconds());
}

bool Movement::isFinished() const {
    return mElapsed >= mDuration || mMotion == nullptr;
}
