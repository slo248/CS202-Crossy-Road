#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "Category.hpp"
#include "Character.hpp"
#include "DataTables.hpp"
#include "Obstacle.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

// Temporary solution for mType being changed during runtime:
// const LaneType: failed
// const LaneTypeHolder with const LaneType: failed
// const LaneTypeHolder with const LaneType*: passed
// static map: passed
static std::unordered_map<Lane*, std::pair<LaneType, Lane::SpawnSide>> laneMap;

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}

Lane::Lane(
    LaneType type, const TextureHolder& textures, bool isBufferLane,
    float levelScale
)
    : mType(type),
      mRandomFactor(1.f),
      mChildLane(nullptr),
      mTrafficLight(nullptr),
      mSpawnInterval(Table[type].spawnInterval),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {
    laneMap[this].first = type;
    // std::cout << "Lane " << this << " is created\n";

    // Origin
    // Death Experience: origin must be set for mSprite, not the Lane itself!
    mSprite.setOrigin(0, DEFAULT_CELL_LENGTH / 2);
    // If it works, then don't touch it!

    // Object factory
    mObjectFactory =
        std::make_unique<ObjectFactory>(textures, type, levelScale);

    // Spawn initial objects
    if (type == LaneType::River) {
        mSpawnSide = static_cast<SpawnSide>(rand() % 2);
        return;
    } else {
        int isHavingTrafficLight =
            isBufferLane ? 0 : (rand() % 3) - 1;  // -1, 0 , 1
        mSpawnSide =
            isHavingTrafficLight == 0
                ? None
                : static_cast<SpawnSide>((isHavingTrafficLight + 1) / 2);

        // Spawn initial traffic light or obstacles if having no traffic light
        // or buffer lane
        // This is pretty dangerous
        if (!isHavingTrafficLight) {
            spawnObstacles(isBufferLane);
        } else {
            spawnTrafficLight();
        }
    }
    laneMap[this].second = mSpawnSide;
}

Lane::~Lane() {
    // std::cout << "Lane " << laneMap[this] << " is deleted\n";
    laneMap.erase(this);
}

unsigned int Lane::getCategory() const { return Category::Lane; }

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

sf::FloatRect Lane::getLocalBounds() const { return mSprite.getLocalBounds(); }

Lane* Lane::getChildLane() { return mChildLane; }

// Check for the next position of the player
sf::Vector2f Lane::checkMoveablePlayer(
    Character* player, Character::Direction direction
) {
    sf::FloatRect playerBound = player->getBoundingRect();
    switch (direction) {
        case Character::Direction::ToLeft: {
            playerBound.left -= DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToRight: {
            playerBound.left += DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToLower: {
            playerBound.top += DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToUpper: {
            playerBound.top -= DEFAULT_CELL_LENGTH;
            break;
        }
    }

    // playerBound position is at top left corner
    sf::Vector2f incommingPosition =
        playerBound.getPosition() + playerBound.getSize() / 2.f;

    if (incommingPosition.x < 0 ||
        incommingPosition.x > DEFAULT_CELLS_PER_LANE * DEFAULT_CELL_LENGTH) {
        return player->getPosition();
    }

    for (auto& child : mChildren) {
        std::cout << child->getCategory() << '\n';
        if (collision(playerBound, child->getBoundingRect())) {
            std::cout << "Collided with sth\n";

            switch (child->getCategory()) {
                case Category::Decoration: {
                    // Player jumps to the log -> early return
                    Obstacle* log = static_cast<Obstacle*>(child.get());
                    player->setVelocity(log->getVelocity());

                    // Need some alignment later
                    incommingPosition.x = child->getWorldPosition().x +
                                          child->getBoundingRect().width / 4.f;
                    // std::cout << "Player position: " << incommingPosition.x
                    //           << '\n';
                    // std::cout << "Log position: " <<
                    // child->getWorldPosition().x
                    //           << '\n';
                    // std::cout << "Log width: " <<
                    // child->getBoundingRect().width
                    //           << '\n';
                    return incommingPosition;
                }

                case Category::Obstacle: {
                    // Player stands still
                    return player->getPosition();
                }

                default: {
                    // Player jumps to the incomming position
                    break;
                }
            }
        }
    }

    // Align incomming position (need optimization)
    incommingPosition.x =
        round(
            (incommingPosition.x - DEFAULT_CELL_LENGTH / 2.f) /
            DEFAULT_CELL_LENGTH
        ) * DEFAULT_CELL_LENGTH +
        DEFAULT_CELL_LENGTH / 2.f;
    std::cout << incommingPosition.x << '\n';
    return incommingPosition;
}

// Check for the current position of the player
bool Lane::isCollidedWithPlayer(Character* player) {
    sf::FloatRect playerBound = player->getBoundingRect();

    // Detect any collision with enemy
    for (auto& child : mChildren) {
        if (collision(playerBound, child->getBoundingRect())) {
            switch (child->getCategory()) {
                case Category::Enemy: {
                    return true;
                }

                case Category::Decoration: {
                    Obstacle* log = static_cast<Obstacle*>(child.get());
                    player->setVelocity(log->getVelocity());
                    return false;
                }

                default: {
                    break;
                }
            }
        }
    }

    // If no collision happened, check if player is on the river and not moving
    if (mType == LaneType::River && player->getVelocity().x == 0) {
        // std::cout << "Jumped to the river\n";
        return true;
    }

    // No collision, not on the river -> totally normal
    return false;
}

float Lane::getRandomFactor() const { return mRandomFactor; }

void Lane::attachChild(SceneNode::Ptr child) {
    if (child->getCategory() == Category::Lane) {
        mChildLane = static_cast<Lane*>(child.get());
        if (mChildLane) {
            float childRandomFactor = mChildLane->getRandomFactor();
            if (childRandomFactor > 1.0) {
                mRandomFactor = 1.0;
            } else if (childRandomFactor < 1.0) {
                mRandomFactor = 0.7;
            } else {
                mRandomFactor = 1.3;
            }

            mChildLane->setPosition(0, DEFAULT_CELL_LENGTH);
        }
    }
    SceneNode::attachChild(std::move(child));
}

void Lane::spawnObstacles(bool isBufferLane) {
    std::unique_ptr<Obstacle> obstacle;
    int count = (rand() % 3) + 3;  // 3, 4, 5 obstacles per lane
    int slot = -1;

    // Divide in half for better objects distribution
    // std::cout << count << '\n';
    for (int i = 0; i < count / 2; ++i) {
        slot = random(slot + 1, DEFAULT_CELLS_PER_LANE / 2 - count / 2 - 1 + i);
        obstacle = mObjectFactory->createObstacle();
        obstacle->setPosition(slotToPosition(slot), 0);
        // std::cout << slot << ' ';
        attachChild(std::move(obstacle));
    }

    // Reserve the 7th slot for player if this is a buffer lane
    slot = -1 + isBufferLane;
    for (int i = 0; i < count / 2; ++i) {
        slot = random(slot + 1, DEFAULT_CELLS_PER_LANE / 2 - count / 2 - 1 + i);
        obstacle = mObjectFactory->createObstacle();
        obstacle->setPosition(
            slotToPosition(slot + DEFAULT_CELLS_PER_LANE / 2), 0
        );
        // std::cout << slot << ' ';
        attachChild(std::move(obstacle));
    }
    // std::cout << '\n';
}

void Lane::spawnTrafficLight() {
    std::unique_ptr<TrafficLight> trafficLight =
        mObjectFactory->createTrafficLight();

    mTrafficLight = static_cast<TrafficLight*>(trafficLight.get());
    int slot = (rand() % 8) + 3;  // 3 -> 11

    trafficLight->setPosition(slotToPosition(slot), 0);
    attachChild(std::move(trafficLight));
}

void Lane::spawnGroundEnemy() {
    std::unique_ptr<Character> groundEnemy(mObjectFactory->createGroundEnemy());

    // -1 or 1 based on spawn side
    groundEnemy->setScaleNormalVelocity(1 - (mSpawnSide << 1));

    // slot is -1 or 12 based on spawn side
    groundEnemy->setPosition(
        slotToPosition((DEFAULT_CELLS_PER_LANE + 1) * mSpawnSide - 1), 0
    );
    attachChild(std::move(groundEnemy));
}

void Lane::spawnAirEnemy() {
    std::unique_ptr<Character> airEnemy(mObjectFactory->createAirEnemy());

    // -1 or 1 based on spawn side
    airEnemy->setScaleNormalVelocity(1 - (mSpawnSide << 1));

    // slot is -1 or 12 based on spawn side
    airEnemy->setPosition(
        slotToPosition((DEFAULT_CELLS_PER_LANE + 1) * mSpawnSide - 1), 0
    );
    attachChild(std::move(airEnemy));
}

void Lane::spawnLog() {
    std::unique_ptr<Obstacle> log(mObjectFactory->createLog());

    // -1 or 1 based on spawn side
    log->setScaleNormalVelocity((1 - (mSpawnSide << 1)) * mRandomFactor);

    // slot is -1 or 14 based on spawn side
    log->setPosition(
        // slotToPosition(DEFAULT_CELLS_PER_LANE / 2), 0
        slotToPosition((DEFAULT_CELLS_PER_LANE + 1) * mSpawnSide - 1), 0
    );
    attachChild(std::move(log));
}

bool isAirEnemy(Character* character) {
    Character::Type characterType = character->getType();
    return characterType == Character::Type::Bee ||
           characterType == Character::Type::Bird ||
           characterType == Character::Type::BeeBoss ||
           characterType == Character::Type::BombBat;
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    mSpawnInterval += dt;

    // In case unknown changes happen
    mType = laneMap[this].first;
    mSpawnSide = laneMap[this].second;

    // std::cout << this << ' ' << mType << " updating";
    if (mType == LaneType::River) {
        // std::cout << " river\n";

        if (mSpawnInterval >= Table[mType].spawnInterval) {
            float tmp = Table[mType].spawnInterval.asSeconds();
            mSpawnInterval = sf::seconds((float)tmp * (rand() % 3 + 1) / 5);
            spawnLog();
            // std::cout << this << " spawn a log (" <<
            // mSpawnInterval.asSeconds()
            //   << ")\n";
            // mSpawnInterval -= Table[mType].spawnInterval;
        }

        return;
    }
    // std::cout << '\n';

    if (!mTrafficLight) {
        return;
    }

    mSpawnInterval += dt;
    if (mSpawnInterval >= Table[mType].spawnInterval) {
        mSpawnInterval = sf::Time::Zero;
        if (mTrafficLight->getColor() == TrafficLight::Color::Green) {
            // spawnGroundEnemy();
        }
    }

    int times = 1 - (mSpawnSide << 1);

    TrafficLight::Phase currentPhase = mTrafficLight->getPhase();
    Character* character;
    switch (currentPhase) {
        case TrafficLight::Phase::RedToGreen: {
            for (int i = 0; i < mChildren.size(); ++i) {
                if (mChildren[i]->getCategory() == Category::Enemy) {
                    character = static_cast<Character*>(mChildren[i].get());
                    if (character) {
                        character->setScaleNormalVelocity(times);
                    }
                }
            }
            // spawnAirEnemy();
            break;
        }

        case TrafficLight::Phase::GreenToYellow: {
            for (int i = 0; i < mChildren.size(); ++i) {
                if (mChildren[i]->getCategory() == Category::Enemy) {
                    character = static_cast<Character*>(mChildren[i].get());
                    if (character && !isAirEnemy(character)) {
                        sf::Vector2f currentVelocity = character->getVelocity();
                        character->setScaleNormalVelocity(times * 0.25);
                    }
                }
            }
            // spawnAirEnemy();
            break;
        }

        case TrafficLight::Phase::YellowToRed: {
            for (int i = 0; i < mChildren.size(); ++i) {
                character = static_cast<Character*>(mChildren[i].get());
                if (character && !isAirEnemy(character)) {
                    character->setVelocity(0, 0);
                }
            }
            // spawnAirEnemy();
            break;
        }
    }
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    // states.transform *= getTransform();
    target.draw(mSprite, states);
}

void Lane::updateMovementPattern(sf::Time dt) {}

void createMultipleLanes(
    const TextureHolder& textures, int laneNumber, Lane::Ptr& topLane,
    Lane*& botLane, bool isBuffer, float levelScale
) {
    // If these are buffer lanes, then they do not contain river
    int laneTypeCount = LaneType::TypeCount - isBuffer;
    std::cout << laneTypeCount << '\n';

    // Bottom lane
    LaneType randomLaneType = static_cast<LaneType>(rand() % laneTypeCount);
    Lane::Ptr lane(std::make_unique<Lane>(randomLaneType, textures, isBuffer));

    botLane = lane.get();

    while (--laneNumber) {
        std::cout << "Lane of type " << randomLaneType << " is created\n";
        randomLaneType = static_cast<LaneType>(rand() % laneTypeCount);

        Lane::Ptr parentLane(std::make_unique<Lane>(
            randomLaneType, textures, isBuffer, levelScale
        ));
        parentLane->attachChild(std::move(lane));
        lane = std::move(parentLane);
    }

    topLane = std::move(lane);
}
