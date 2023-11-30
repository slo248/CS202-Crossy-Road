#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>

#include "Category.hpp"
#include "Character.hpp"
#include "DataTables.hpp"
#include "Obstacle.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}

Lane::Lane(
    LaneType type, const TextureHolder& textures, Ptr childLane,
    float levelScale
)
    : mType(type),
      mTrafficLight(nullptr),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {
    // Set up children lane
    if (childLane) {
        mChildLane = static_cast<Lane*>(childLane.get());
        mChildLane->setPosition(0, DEFAULT_CELL_LENGTH);
        attachChild(std::move(childLane));
    } else {
        mChildLane = nullptr;
    }

    // Origin
    setOrigin(0, mSprite.getLocalBounds().height / 2.f);

    // Object factory
    int isHavingTrafficLight = (rand() % 3) - 1;  // -1, 0 ,1
    mSpawnSide = static_cast<SpawnSide>(isHavingTrafficLight + 1);
    mObjectFactory =
        std::make_unique<ObjectFactory>(textures, type, levelScale);

    // Spawn initial traffic light or obstacles
    if (isHavingTrafficLight) {
        spawnTrafficLight();
    } else {
        spawnObstacles();
        mTrafficLight = nullptr;
    }
}

unsigned int Lane::getCategory() const { return Category::Lane; }

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

Lane* Lane::getChildLane() { return mChildLane; }

bool Lane::checkMovablePlayer(
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

void Lane::spawnObstacles() {
    std::unique_ptr<Obstacle> obstacle;
    int count = (rand() % 3) + 3;  // 3, 4, 5 obstacles per lane
    int slot = 0;

    for (int i = 0; i < count; ++i) {
        slot = random(slot, 12 - count);
        obstacle = mObjectFactory->createObstacle();
        obstacle->setPosition(slotToPosition(slot), 0);
        attachChild(std::move(obstacle));
    }
}

void Lane::spawnTrafficLight() {
    std::unique_ptr<TrafficLight> trafficLight =
        mObjectFactory->createTrafficLight();
    mTrafficLight = static_cast<TrafficLight*>(trafficLight.get());
    int slot = (rand() % 8) + 2;  // 2 -> 9

    trafficLight->setPosition(slotToPosition(slot), 0);
    attachChild(std::move(trafficLight));
}

void Lane::spawnGroundEnemy() {
    std::unique_ptr<Character> groundEnemy =
        mObjectFactory->createGroundEnemy();
    // -1 or 1 based on spawn side
    groundEnemy->setScaleNormalVelocity(mSpawnSide << 1 - 1);
    // slot is -1 or 12 based on spawn side
    setPosition(slotToPosition(13 * mSpawnSide - 1), 0);
    attachChild(std::move(groundEnemy));
}

void Lane::spawnAirEnemy() {
    std::unique_ptr<Character> airEnemy = mObjectFactory->createAirEnemy();
    // -1 or 1 based on spawn side
    airEnemy->setScaleNormalVelocity(mSpawnSide << 1 - 1);
    // slot is -1 or 12 based on spawn side
    setPosition(slotToPosition(13 * mSpawnSide - 1), 0);
    attachChild(std::move(airEnemy));
}

void Lane::spawnLog() {
    std::unique_ptr<Obstacle> log(mObjectFactory->createLog());
    // -1 or 1 based on spawn side
    log->setScaleNormalVelocity(mSpawnSide << 1 - 1);
    // slot is -1 or 12 based on spawn side
    setPosition(slotToPosition(13 * mSpawnSide - 1), 0);
    attachChild(std::move(log));
}

bool isAirEnemy(Character* character) {
    Character::Type tmp = character->getType();
    return tmp == Character::Type::Bee || tmp == Character::Type::Bird ||
           tmp == Character::Type::BeeBoss || tmp == Character::Type::BombBat;
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    if (!mTrafficLight) {
        if (mType == LaneType::River) {
            mSpawnInterval += dt;
            if (mSpawnInterval >= Table[mType].spawnInterval) {
                spawnLog();
            }
        }
        return;
    }

    mSpawnInterval += dt;
    if (mSpawnInterval >= Table[mType].spawnInterval) {
        mSpawnInterval = sf::Time::Zero;
        if (mTrafficLight->getColor() == TrafficLight::Color::Green) {
            spawnGroundEnemy();
        }
    }

    TrafficLight::Phase currentPhase = mTrafficLight->getPhase();
    Character* character;
    switch (currentPhase) {
        case TrafficLight::Phase::RedToGreen: {
            for (int i = 0; i < mChildren.size(); ++i) {
                if (mChildren[i]->getCategory() == Category::Character) {
                    character = static_cast<Character*>(mChildren[i].get());
                    if (character) {
                        character->setScaleNormalVelocity(1);
                    }
                }
            }
            spawnAirEnemy();
            break;
        }

        case TrafficLight::Phase::GreenToYellow: {
            for (int i = 0; i < mChildren.size(); ++i) {
                if (mChildren[i]->getCategory() == Category::Character) {
                    character = static_cast<Character*>(mChildren[i].get());
                    if (character && !isAirEnemy(character)) {
                        sf::Vector2f currentVelocity = character->getVelocity();
                        character->setScaleNormalVelocity(0.25);
                    }
                }
            }
            spawnAirEnemy();
            break;
        }

        case TrafficLight::Phase::YellowToRed: {
            for (int i = 0; i < mChildren.size(); ++i) {
                character = static_cast<Character*>(mChildren[i].get());
                if (character) {
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
    target.draw(mSprite, states);
}

void Lane::updateMovementPattern(sf::Time dt) {}

Lane::Ptr createMultipleLanes(const TextureHolder& textures, int laneNumber) {
    Lane::Ptr lane(
        new Lane(static_cast<LaneType>(rand() % LaneType::TypeCount), textures)
    );

    while (--laneNumber) {
        Lane::Ptr parentLane(new Lane(
            static_cast<LaneType>(rand() % LaneType::TypeCount), textures,
            std::move(lane)
        ));
        lane = std::move(parentLane);
    }

    return lane;
}

float slotToPosition(int slot) {
    return DEFAULT_CELL_LENGTH * slot + DEFAULT_CELL_LENGTH / 2;
}
