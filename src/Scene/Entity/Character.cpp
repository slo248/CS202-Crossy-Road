#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "Lane.hpp"
#include "Motion.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

namespace {
const std::vector<CharacterData> Table = initializeCharacterData();
}

Character::Character(Type type, const TextureHolder& textures, float levelScale)
    : Entity(sf::Vector2f(Table[type].normalSpeed * levelScale, 0)),
      mType(type),
      mMovement(this) {
    mAnimation.setTexture(textures.get(Table[type].texture));
    mAnimation.setFrameSize(Table[type].textureRect.getSize());
    mAnimation.setNumFrames(6);  // Data table
    mAnimation.setDuration(sf::seconds(1));
    mAnimation.setRepeating(true);

    centerOrigin<Animation>(mAnimation);
}

unsigned int Character::getCategory() const { return Category::Character; }

sf::FloatRect Character::getBoundingRect() const {
    return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

sf::FloatRect Character::getLocalBounds() const {
    return mAnimation.getLocalBounds();
}

Character::Type Character::getType() const { return mType; }

void Character::moveCharacter(Direction direction) {
    switch (direction) {
        case ToLeft:
        case ToRight: {
            if (mCurrentLane->checkMoveablePlayer(this, direction)) {
                int coefficient = (direction == ToLeft) ? -1 : 1;
                sf::Vector2f incomingPosition(
                    getPosition().x + coefficient * DEFAULT_CELL_LENGTH,
                    getPosition().y
                );
                mMovement.setup(incomingPosition, Motion::Sigmoid());
            }
            break;
        }
        case ToUpper:
        case ToLower: {
            Lane* nextLane = (direction == ToUpper)
                                 ? static_cast<Lane*>(mCurrentLane->getParent())
                                 : mCurrentLane->getChildLane();

            if (nextLane && nextLane->checkMoveablePlayer(this, direction)) {
                int coefficient = (direction == ToLeft) ? -1 : 1;
                sf::Vector2f incomingPosition(
                    getPosition().x,
                    getPosition().y + coefficient * DEFAULT_CELL_LENGTH
                );
                mMovement.setup(incomingPosition, Motion::Sigmoid());
            }
            break;
        }
    }
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
    mAnimation.update(dt);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mAnimation, states);
}

void Character::updateMovementPattern(sf::Time dt) {}
