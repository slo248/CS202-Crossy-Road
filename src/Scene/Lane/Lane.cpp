#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}

Lane::Lane(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {}

unsigned int Lane::getCategory() const { return Category::Lane; }

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
    ;
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Lane::updateMovementPattern(sf::Time dt) {}
