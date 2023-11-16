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
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {}

unsigned int Obstacle::getCategory() const { return Category::Obstacle; }

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
    ;
}

void Obstacle::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Obstacle::updateMovementPattern(sf::Time dt) {
    if (!mIsHavingMovement) {
        return;
    }
}
