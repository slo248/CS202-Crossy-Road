#include "Enemy.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<EnemyData> Table = initializeEnemyData();
}

Enemy::Enemy(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {}

unsigned int Enemy::getCategory() const { return Category::Enemy; }

sf::FloatRect Enemy::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
    ;
}

void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Enemy::updateMovementPattern(sf::Time dt) {}
