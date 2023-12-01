#include "Obstacle.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(Type type, const TextureHolder& textures, float levelScale)
    : Entity(sf::Vector2f(Table[type].normalSpeed * levelScale, 0)),
      mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect),
      mIsBlockingPlayer(Table[type].isBlockingPlayer) {}

unsigned int Obstacle::getCategory() const {
    return mIsBlockingPlayer ? Category::Obstacle : Category::Decoration;
}

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

sf::FloatRect Obstacle::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

void Obstacle::updateCurrent(sf::Time dt, CommandQueue& commands) {
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Obstacle::updateMovementPattern(sf::Time dt) {}
