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
      mIsInMovement(false) {
    CharacterData data = Table[type];
    for (int i = 0; i < data.textures.size(); ++i) {
        mAnimations.push_back(
            Animation(textures.get(data.textures[i]), data.frameSize)
        );
    }

    mCurrentAnimation = &mAnimations[CharacterData::Direction::Idle];
    mCurrentAnimation->play();
    mCurrentAnimation->setRepeat(true);
    // centerOrigin(*this);
}

Character::Character(
    std::istream& in, Type type, const TextureHolder& textures, float levelScale
)
    : Character(type, textures, levelScale) {
    loadCurrent(in);
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

    // std::cout << " destroyed!\n";
}

unsigned int Character::getCategory() const {
    if (mType >= BeeBoss && mType <= Mino) return Category::Enemy;
    if (mType >= Archer && mType <= Wizard) return Category::Player;
    return Category::None;
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
    if (!mMovement.isFinished() || SceneNode::isMarkedForRemoval()) return;
    // Remember to initialize
    Animation* nextAnimation = &mAnimations[CharacterData::Direction::Idle];
    Lane* nextLane = nullptr;

    switch (direction) {
        case ToLeft: {
            nextLane = mCurrentLane;
            nextAnimation = &mAnimations[CharacterData::Direction::ToLeft];
            // std::cout << "Move to left\n";
            break;
        }
        case ToRight: {
            nextLane = mCurrentLane;
            nextAnimation = &mAnimations[CharacterData::Direction::ToRight];
            // std::cout << "Move to right\n";
            break;
        }

        case ToUpper: {
            nextLane = mCurrentLane->getParentLane();
            // std::cout << "Move to upper\n";
            break;
        }

        case ToLower: {
            nextLane = mCurrentLane->getChildLane();
            // std::cout << "Move to lower\n";
            break;
        }
    }

    if (!nextLane) {
        std::cout << "Jumped to undefined lane!!!\n";
        return;
    }

    sf::Vector2f incomingPosition =
        nextLane->checkMoveablePlayer(this, direction);
    if (incomingPosition != getWorldPosition()) {
        mCurrentAnimation = nextAnimation;
        mCurrentLane = nextLane;

        mCurrentAnimation->play();
        mMovement.setup(incomingPosition, Motion::Linear());
        mIsInMovement = true;
    }
    // std::cout << mCurrentLane->getType() << '\n';
}

// Check if character is ready for removed (death animation is finished)
bool Character::isMarkedForRemoval() const {
    if (getCategory() == Category::Player)
        return SceneNode::isMarkedForRemoval() && mCurrentAnimation &&
               !mCurrentAnimation->isInProgress();

    return SceneNode::isMarkedForRemoval();
}

void Character::setCurrentLane(Lane* lane) { mCurrentLane = lane; }

bool Character::isInMovement() const { return mIsInMovement; }

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    Entity::updateCurrent(dt, commands);

    // Only for the death of player
    if (!SceneNode::isMarkedForRemoval() && getCategory() == Category::Player &&
        mCurrentLane && mCurrentLane->isCollidedWithPlayer(this)) {
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

    // By default, only player can set mIsInMovement to true
    if (mIsInMovement) {
        // The reason why player can't move along with the log
        // This set player's velocity to 0 everytime the player is not in a
        // movement
        mMovement.update(dt);
    }
    if (mMovement.isFinished()) {
        mIsInMovement = false;
    }
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(*mCurrentAnimation, states);
}

void Character::saveCurrent(std::ostream& out) const {
    Category::Type category = static_cast<Category::Type>(getCategory());
    out << category << ' ' << mType << ' ';
    if (category == Category::Player) {
        out << getWorldPosition().x << ' ' << getWorldPosition().y << ' '
            << getVelocity().x << '\n';

    } else {
        out << getPosition().x << ' ' << getVelocity().x << '\n';
    }
}

void Character::loadCurrent(std::istream& in) {
    if (getCategory() == Category::Player) {
        float x, y, velocity;
        in >> x >> y >> velocity;
        setPosition(x, y);
        setVelocity(velocity, 0);
        return;
    }

    float x, velocity;
    in >> x >> velocity;
    setPosition(x, 0);
    setVelocity(velocity, 0);
}
