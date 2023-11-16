#include "Animal.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<AnimalData> Table = initializeAnimalData();
}

Animal::Animal(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {}

unsigned int Animal::getCategory() const { return Category::Animal; }

sf::FloatRect Animal::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
    ;
}

void Animal::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void Animal::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Animal::updateMovementPattern(sf::Time dt) {}
