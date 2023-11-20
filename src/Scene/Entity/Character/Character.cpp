#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

namespace {
const std::vector<CharacterData> Table = initializeCharacterData();
}

Character::Character(Type type, const TextureHolder& textures) : mType(type) {
    mAnimation.setTexture(textures.get(Table[type].texture));
    mAnimation.setFrameSize(Table[type].textureRect.getSize());
    mAnimation.setNumFrames(6);  // Data table
    mAnimation.setDuration(sf::seconds(1));
    mAnimation.setRepeating(true);

    centerOrigin(mAnimation);
}

unsigned int Character::getCategory() const { return Category::Character; }

sf::FloatRect Character::getBoundingRect() const {
    return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mAnimation, states);
}

void Character::updateMovementPattern(sf::Time dt) {}
