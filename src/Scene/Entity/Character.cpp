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
      mCurrentLane(nullptr) {
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
    Animation* mNextAnimation;
    switch (direction) {
        case ToLeft:
            std::cout << "Move to left\n";
            mNextAnimation = &mAnimations[CharacterData::Direction::ToLeft];
            break;
        case ToRight:
            std::cout << "Move to right\n";
            mNextAnimation = &mAnimations[CharacterData::Direction::ToRight];
            break;
        case ToUpper:
            std::cout << "Move to upper\n";
            break;
        case ToLower:
            std::cout << "Move to lower\n";
            break;
    }
    sf::Vector2f incomingPosition;
    Lane* nextLane = nullptr;

    switch (direction) {
        case ToLeft:
        case ToRight: {
            nextLane = mCurrentLane;
            break;
        }

        case ToUpper: {
            nextLane = static_cast<Lane*>(mCurrentLane->getParent());
            break;
        }

        case ToLower: {
            nextLane = mCurrentLane->getChildLane();
            break;
        }
    }

    if (!nextLane) {
        std::cout << "Jumped to undefined lane!!!\n";
        return;
    }

    incomingPosition = nextLane->checkMoveablePlayer(this, direction);
    if (incomingPosition != getWorldPosition()) {
        mCurrentAnimation = mNextAnimation;
        mCurrentLane = nextLane;

        mCurrentAnimation->play();
        mMovement.setup(incomingPosition, Motion::Linear());
    }
}

bool Character::isMarkedForRemoval() const {
    if (getCategory() == Category::Player)
        return SceneNode::isMarkedForRemoval() && mCurrentAnimation &&
               !mCurrentAnimation->isInProgress();

    return SceneNode::isMarkedForRemoval();
}

void Character::setCurrentLane(Lane* lane) { mCurrentLane = lane; }

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // updateMovementPattern(dt);
    if (getCategory() != Category::Player) Entity::updateCurrent(dt, commands);

    if (getCategory() == Category::Player && mCurrentLane &&
        mCurrentLane->isCollidedWithPlayer(this)) {
        destroy();
        // The last animation of player is "dead animation"
        mCurrentAnimation = &mAnimations[mAnimations.size() - 1];
        mCurrentAnimation->update(dt);
        std::cout << "Player is dead!\n";
        return;
    }

    Animation* tmpAnimation;
    if (getVelocity().x == 0) {
        tmpAnimation = &mAnimations[CharacterData::Direction::Idle];
    } else if (getVelocity().x > 0) {
        tmpAnimation = &mAnimations[CharacterData::Direction::ToRight];
    } else {
        tmpAnimation = &mAnimations[CharacterData::Direction::ToLeft];
    }

    if (!mCurrentAnimation || mCurrentAnimation != tmpAnimation) {
        mCurrentAnimation = tmpAnimation;
        mCurrentAnimation->play();
        mCurrentAnimation->setRepeat(true);
    }

    mCurrentAnimation->update(dt);
    mMovement.update(dt);
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(*mCurrentAnimation, states);
}

void Character::updateMovementPattern(sf::Time dt) {}
