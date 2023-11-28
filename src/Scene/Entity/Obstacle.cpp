#include "Obstacle.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(Type type, const TextureHolder& textures)
    : Entity(sf::Vector2f(Table[type].normalSpeed, 0)),
      mType(type),
      mIsBlockingPlayer(Table[type].isBlockingPlayer) {
    mAnimation.setTexture(textures.get(Table[type].texture));
    mAnimation.setFrameSize(Table[type].textureRect.getSize());
    mAnimation.setNumFrames(6);  // Data table
    mAnimation.setDuration(sf::seconds(1));
    mAnimation.setRepeating(true);
}

unsigned int Obstacle::getCategory() const {
    return mIsBlockingPlayer ? Category::Obstacle : Category::Decoration;
}

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

sf::FloatRect Obstacle::getLocalBounds() const {
    return mAnimation.getLocalBounds();
}

void Obstacle::updateCurrent(sf::Time dt, CommandQueue& commands) {
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mAnimation, states);
}

void Obstacle::updateMovementPattern(sf::Time dt) {}
