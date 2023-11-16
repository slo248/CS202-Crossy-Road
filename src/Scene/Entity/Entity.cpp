#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity) { this->mVelocity = velocity; }

void Entity::setVelocity(float x, float y) {
    this->mVelocity = sf::Vector2f(x, y);
}

sf::Vector2f Entity::getVelocity() { return mVelocity; }

unsigned int Entity::getDirection() { return mDirection; }

void Entity::setDirectionIndex(Direction direction) { mDirection = direction; }

void Entity::updateCurrent(sf::Time dt) { move(mVelocity * dt.asSeconds()); }
