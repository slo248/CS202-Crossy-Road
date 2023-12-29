#include "Entity.hpp"

Entity::Entity(sf::Vector2f normalVelocity)
    : mNormalVelocity(normalVelocity), mTemporaryFactor(1.f) {}

void Entity::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

void Entity::setVelocity(float x, float y) { mVelocity = sf::Vector2f(x, y); }

void Entity::setScaleNormalVelocity(float times) {
    mVelocity = mNormalVelocity * mTemporaryFactor * times;
}

void Entity::setTemporaryNormalVelocity(float temporaryFactor) {
    mTemporaryFactor = temporaryFactor;
}

void Entity::accelerate(sf::Vector2f velocity) { mVelocity += velocity; }

void Entity::accelerate(float vx, float vy) {
    mVelocity.x += vx;
    mVelocity.y += vy;
}

sf::Vector2f Entity::getVelocity() const { return mVelocity; }

sf::Vector2f Entity::getNormalVelocity() const {
    return mNormalVelocity * mTemporaryFactor;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
    move(mVelocity * dt.asSeconds());
}
