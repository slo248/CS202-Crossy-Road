#include "Entity.hpp"

Entity::Entity(sf::Vector2f normalVelocity) : mVelocity(normalVelocity), mNormalVelocity(normalVelocity) {}

void Entity::setVelocity(sf::Vector2f velocity) { this->mVelocity = velocity; }

void Entity::setVelocity(float x, float y) {
    this->mVelocity = sf::Vector2f(x, y);
}

void Entity::setScaleNormalVelocity(float times) {
    this->mVelocity = mNormalVelocity * times;
}

void Entity::accelerate(sf::Vector2f velocity) { mVelocity += velocity; }

void Entity::accelerate(float vx, float vy) {
    mVelocity.x += vx;
    mVelocity.y += vy;
}

sf::Vector2f Entity::getVelocity() { return mVelocity; }

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
    move(mVelocity * dt.asSeconds());
}
