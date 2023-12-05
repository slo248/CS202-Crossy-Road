#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

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
    CharacterData data = Table[type];
    for (int i = 0; i < data.textures.size(); ++i) {
        mAnimations.push_back(Animation(
            textures.get(data.textures[i]), data.frameSize, data.numFrames
        ));
    }
    mCurrentAnimation = &mAnimations[mAnimations.size() - 1];
    // centerOrigin(*this);
}

Character::~Character() {
    switch (mType) {
        case Bee:
            std::cout << "Bee";
            break;

        case Bird:
            std::cout << "Bird";
            break;

        case Crocodile:
            std::cout << "Crocodile";
            break;

        case Dog:
            std::cout << "Dog";
            break;

        case Frog:
            std::cout << "Frog";
            break;

        case Rabbit:
            std::cout << "Rabbit";
            break;

        case Sheep:
            std::cout << "Sheep";
            break;

        case Turtle:
            std::cout << "Turtle";
            break;

        case BeeBoss:
            std::cout << "BeeBoss";
            break;

        case BombBat:
            std::cout << "BombBat";
            break;

        case Fishmen:
            std::cout << "Fishmen";
            break;

        case Orc:
            std::cout << "Orc";
            break;

        case Zombie:
            std::cout << "Zombie";
            break;
    }
    std::cout << " destroyed!\n";
}

unsigned int Character::getCategory() const {
    if (mType == Archer || mType == Enchantress || mType == Knight ||
        mType == Musketeer || mType == Swordsman || mType == Wizard)
        return Category::Player;
    return Category::Enemy;
}

sf::FloatRect Character::getBoundingRect() const {
    return getWorldTransform().transformRect(mCurrentAnimation->getGlobalBounds(
    ));
}

sf::FloatRect Character::getLocalBounds() const {
    return mAnimations[0].getLocalBounds();
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
    // updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);

    if (getVelocity().x == 0) {
        mCurrentAnimation = &mAnimations[CharacterData::Direction::Idle];
        mCurrentAnimation->play();

    } else if (getVelocity().x > 0) {
        mCurrentAnimation = &mAnimations[CharacterData::Direction::ToRight];
        mCurrentAnimation->play();

    } else {
        mCurrentAnimation = &mAnimations[CharacterData::Direction::ToLeft];
        mCurrentAnimation->play();
    }
    mCurrentAnimation->update(dt);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(*mCurrentAnimation, states);
}

void Character::updateMovementPattern(sf::Time dt) {}
