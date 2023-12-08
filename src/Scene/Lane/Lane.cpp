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
static std::unordered_map<Lane*, int> laneMap;

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}

Lane::Lane(
    LaneType type, const TextureHolder& textures, float levelScale,
    Ptr childLane
)
    : mType(type),
      //   mTypeHolder(new LaneTypeHolder(type)),
      mTrafficLight(nullptr),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect),
      mObjectFactory(std::make_unique<ObjectFactory>(textures, type, levelScale)
      ) {
    laneMap[this] = type;
    // std::cout << "Lane " << this << " is created\n";

    // Set up children lane
    if (childLane) {
        float childRandomFactor = childLane->getRandomFactor();
        if (childRandomFactor > 1.0) {
            mRandomFactor = 1.0;
        } else if (childRandomFactor < 1.0) {
            mRandomFactor = 0.7;
        } else {
            mRandomFactor = 1.3;
        }

        mChildLane = childLane.get();
        attachChild(std::move(childLane));
        mChildLane->setPosition(0, DEFAULT_CELL_LENGTH);
    } else {
        mChildLane = nullptr;
        mRandomFactor = 1.0;
    }

    // Origin
    // Death Experience: origin must be set for mSprite, not the Lane itself!
    mSprite.setOrigin(0, DEFAULT_CELL_LENGTH / 2);
    // If it works, then don't touch it!

    // Object factory for Non-River
    int isHavingTrafficLight = (rand() % 3) - 1;  // -1, 0 , 1
    mSpawnSide = isHavingTrafficLight == 0
                     ? None
                     : static_cast<SpawnSide>((isHavingTrafficLight + 1) / 2);

    // For River
    if (type == LaneType::River) {
        mSpawnSide = static_cast<SpawnSide>(rand() % 2);
        mSpawnInterval = Table[type].spawnInterval;
        return;
    }

    // Spawn initial traffic light or obstacles
    if (isHavingTrafficLight) {
        spawnTrafficLight();
    } else {
        spawnObstacles();
    }
}

Lane::~Lane() {
    // std::cout << "Lane " << laneMap[this] << " is deleted\n";
    // delete mTypeHolder;
}

unsigned int Lane::getCategory() const { return Category::Lane; }

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

sf::FloatRect Lane::getLocalBounds() const { return mSprite.getLocalBounds(); }

Lane* Lane::getChildLane() { return mChildLane; }

bool Lane::checkMoveablePlayer(
    Character* player, Character::Direction direction
) {
    sf::FloatRect playerBounds = player->getBoundingRect();
    switch (direction) {
        case Character::Direction::ToLeft: {
            playerBounds.left -= DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToRight: {
            playerBounds.left += DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToLower: {
            playerBounds.top -= DEFAULT_CELL_LENGTH;
            break;
        }

        case Character::Direction::ToUpper: {
            playerBounds.top += DEFAULT_CELL_LENGTH;
            break;
        }
    }
    for (auto& child : mChildren) {
        if (collision(playerBounds, child->getBoundingRect()) &&
            child->getCategory() == Category::Obstacle &&
            player->getCategory() == Category::Player) {
            return false;
        }
    }
    return true;
}

float Lane::getRandomFactor() const { return mRandomFactor; }

void Lane::spawnObstacles() {
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

    slot = -1;
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

    mType = static_cast<LaneType>(laneMap[this]);
    // mType = mTypeHolder->getType();

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
            spawnGroundEnemy();
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
            spawnAirEnemy();
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
            spawnAirEnemy();
            break;
        }

        case TrafficLight::Phase::YellowToRed: {
            for (int i = 0; i < mChildren.size(); ++i) {
                character = static_cast<Character*>(mChildren[i].get());
                if (character && !isAirEnemy(character)) {
                    character->setVelocity(0, 0);
                }
            }
            spawnAirEnemy();
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
    Lane*& botLane, float levelScale
) {
    LaneType tmp = static_cast<LaneType>(rand() % LaneType::TypeCount);
    Lane::Ptr lane(std::make_unique<Lane>(tmp /*LaneType::River*/, textures));

    botLane = lane.get();

    while (--laneNumber) {
        std::cout << "Lane of type " << tmp << " is created\n";
        Lane::Ptr parentLane;
        if (laneNumber & 1) {
            tmp = LaneType::River;
            parentLane = std::make_unique<Lane>(
                tmp, textures, levelScale, std::move(lane)
            );
        } else {
            tmp = static_cast<LaneType>(rand() % LaneType::TypeCount);
            parentLane = std::make_unique<Lane>(
                tmp, textures, levelScale, std::move(lane)
            );
        }
        lane = std::move(parentLane);
    }

    topLane = std::move(lane);
}

float slotToPosition(int slot) {
    return DEFAULT_CELL_LENGTH * slot + DEFAULT_CELL_LENGTH / 2;
}
