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
      mMovement(this),
      mCurrentLane(nullptr),
      mIsMoving(false) {
    CharacterData data = Table[type];
    for (int i = 0; i < data.textures.size(); ++i) {
        mAnimations.push_back(Animation(
            textures.get(data.textures[i]), data.frameSize, data.numFrames
        ));
    }

    mCurrentAnimation = &mAnimations[CharacterData::Direction::Idle];
    mCurrentAnimation->play();
    mCurrentAnimation->setRepeat(true);
    // centerOrigin(*this);
}

Character::~Character() {
    // switch (mType) {
    //     case Bee:
    //         std::cout << "Bee";
    //         break;

    //     case Bird:
    //         std::cout << "Bird";
    //         break;

    //     case Crocodile:
    //         std::cout << "Crocodile";
    //         break;

    //     case Dog:
    //         std::cout << "Dog";
    //         break;

    //     case Frog:
    //         std::cout << "Frog";
    //         break;

    //     case Rabbit:
    //         std::cout << "Rabbit";
    //         break;

    //     case Sheep:
    //         std::cout << "Sheep";
    //         break;

    //     case Turtle:
    //         std::cout << "Turtle";
    //         break;

    //     case BeeBoss:
    //         std::cout << "BeeBoss";
    //         break;

    //     case BombBat:
    //         std::cout << "BombBat";
    //         break;

    //     case Fishmen:
    //         std::cout << "Fishmen";
    //         break;

    //     case Orc:
    //         std::cout << "Orc";
    //         break;

    //     case Zombie:
    //         std::cout << "Zombie";
    //         break;
    // }
    // std::cout << " destroyed!\n";
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
    if (!mMovement.isFinished()) return;
    Animation* nextAnimation;
    sf::Vector2f incomingPosition;
    Lane* nextLane = nullptr;

    switch (direction) {
        case ToLeft: {
            nextLane = mCurrentLane;
            nextAnimation = &mAnimations[CharacterData::Direction::ToLeft];
            std::cout << "Move to left\n";
            break;
        }
        case ToRight: {
            nextLane = mCurrentLane;
            nextAnimation = &mAnimations[CharacterData::Direction::ToRight];
            std::cout << "Move to right\n";
            break;
        }

        case ToUpper: {
            nextLane = dynamic_cast<Lane*>(mCurrentLane->getParent());
            std::cout << "Move to upper\n";
            break;
        }

        case ToLower: {
            nextLane = mCurrentLane->getChildLane();
            std::cout << "Move to lower\n";
            break;
        }
    }

    if (!nextLane) {
        std::cout << "Jumped to undefined lane!!!\n";
        return;
    }

    incomingPosition = nextLane->checkMoveablePlayer(this, direction);
    if (incomingPosition != getWorldPosition()) {
        mCurrentAnimation = nextAnimation;
        mCurrentLane = nextLane;

        mCurrentAnimation->play();
        mMovement.setup(incomingPosition, Motion::Linear());
        mIsMoving = true;
    }
}

// Check if character is ready for removed (death animation is finished)
bool Character::isMarkedForRemoval() const {
    if (getCategory() == Category::Player)
        return SceneNode::isMarkedForRemoval() && mCurrentAnimation &&
               !mCurrentAnimation->isInProgress();

    return SceneNode::isMarkedForRemoval();
}

void Character::setCurrentLane(Lane* lane) { mCurrentLane = lane; }

bool Character::isMoving() const { return mIsMoving; }

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    Entity::updateCurrent(dt, commands);

    // Only for the death of player
    if (getCategory() == Category::Player && mCurrentLane &&
        mCurrentLane->isCollidedWithPlayer(this)) {
        // The last animation of player is "dead animation"
        if (mCurrentAnimation != &mAnimations[mAnimations.size() - 1]) {
            std::cout << "Player is performing death!\n";
            mCurrentAnimation = &mAnimations[mAnimations.size() - 1];
            mCurrentAnimation->play();
            mCurrentAnimation->setRepeat(false);
            destroy();
        }
    }
    // For characters in general, check if character is dead
    else if (!SceneNode::isMarkedForRemoval()) {
        Animation* nextAnimation;

        if (getVelocity().x == 0) {
            nextAnimation = &mAnimations[CharacterData::Direction::Idle];
        } else if (getVelocity().x > 0) {
            nextAnimation = &mAnimations[CharacterData::Direction::ToRight];
        } else {
            nextAnimation = &mAnimations[CharacterData::Direction::ToLeft];
        }

        if (!mCurrentAnimation || mCurrentAnimation != nextAnimation) {
            mCurrentAnimation = nextAnimation;
            mCurrentAnimation->play();
            mCurrentAnimation->setRepeat(true);
        }
    }

    mCurrentAnimation->update(dt);

    // By default, only player can set mIsMoving to true
    if (mIsMoving) {
        // The reason why player can't move along with the log
        // This set player's velocity to 0 everytime the player is not in a
        // movement
        mMovement.update(dt);
    }
    if (mMovement.isFinished()) {
        mIsMoving = false;
    }
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(*mCurrentAnimation, states);
}

void Character::updateMovementPattern(sf::Time dt) {}
