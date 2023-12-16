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
    : Lane(type, textures, levelScale) {
    // Spawn initial objects
    if (type == LaneType::River) {
        mSpawnSide = static_cast<SpawnSide>(rand() % 2);
        mSpawnInterval = sf::seconds(
            (Table[type].spawnInterval.asSeconds() / levelScale) / 1.2
        );
    } else {
        int isHavingTrafficLight =
            isBufferLane ? 0 : (rand() % 3) - 1;  // -1, 0 , 1
        mSpawnSide =
            isHavingTrafficLight == 0
                ? None
                : static_cast<SpawnSide>((isHavingTrafficLight + 1) / 2);

        if (!isHavingTrafficLight) {
            spawnObstacles(isBufferLane);
        } else {
            spawnTrafficLight();
        }
    }
}

Lane::Lane(
    std::istream& in, LaneType type, const TextureHolder& textures,
    float levelScale
)
    : Lane(type, textures, levelScale) {
    loadCurrent(in);
    loadChildren(in, textures);
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

Lane* Lane::getParentLane() { return dynamic_cast<Lane*>(getParent()); }

Lane* Lane::getChildLane() { return mChildLane; }

LaneType Lane::getType() { return mType; }

Lane::SpawnSide Lane::getSpawnSide() { return laneMap[this].second; }

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
                    float alignment = 0.1 * DEFAULT_LOG_SPEED;
                    incommingPosition.x = log->getWorldPosition().x + alignment;
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
        mChildLane = dynamic_cast<Lane*>(child.get());
        if (mChildLane) {
            Lane::SpawnSide childSpawnSide = mChildLane->getSpawnSide();
            if (childSpawnSide == None) {
                mSpawnSide = static_cast<SpawnSide>(rand() % 2);
            } else {
                mSpawnSide = childSpawnSide == Left ? Right : Left;
            }
            laneMap[this].second = mSpawnSide;

            float childRandomFactor = mChildLane->getRandomFactor();
            if (childRandomFactor > 1.f) {
                mRandomFactor = 1.f;
            } else if (childRandomFactor < 1.0) {
                mRandomFactor = 0.85;
            } else {
                mRandomFactor = 1.2;
            }

            mChildLane->setPosition(0, DEFAULT_CELL_LENGTH);
        }
    }
    SceneNode::attachChild(std::move(child));
}

Lane::Lane(LaneType type, const TextureHolder& textures, float levelScale)
    : mType(type),
      mRandomFactor(1),
      mChildLane(nullptr),
      mTrafficLight(nullptr),
      mSpawnInterval(
          sf::seconds((Table[type].spawnInterval.asSeconds() / levelScale))
      ),
      mElapsedTime(mSpawnInterval),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect),
      mObjectFactory(std::make_unique<ObjectFactory>(textures, type, levelScale)
      ) {
    laneMap[this].first = type;

    // Death Experience: origin must be set for mSprite, not the Lane itself!
    mSprite.setOrigin(0, DEFAULT_CELL_LENGTH / 2);
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
    return characterType == Character::Type::BeeBoss ||
           characterType == Character::Type::BombBat;
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    mElapsedTime += dt;

    // In case unknown changes happen
    mType = laneMap[this].first;
    mSpawnSide = laneMap[this].second;

    if (mType == LaneType::River) {
        if (mElapsedTime >= mSpawnInterval) {
            float tmp = mSpawnInterval.asSeconds();
            mElapsedTime = sf::seconds((float)tmp * (rand() % 3 + 1) / 5);
            spawnLog();
        }
        return;
    }

    if (!mTrafficLight) {
        return;
    }

    if (mElapsedTime >= mSpawnInterval) {
        float tmp = mSpawnInterval.asSeconds();
        mElapsedTime = sf::seconds((float)tmp * (rand() % 3 + 1) / 5);
        if (mTrafficLight->getColor() == TrafficLight::Color::Green) {
            spawnGroundEnemy();
        }
    }

    float times = (1 - (mSpawnSide << 1)) * mRandomFactor *
                  ((rand() % 3 + 1) / 20.f + 1.f);

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
            break;
        }

        case TrafficLight::Phase::YellowToRed: {
            for (int i = 0; i < mChildren.size(); ++i) {
                character = static_cast<Character*>(mChildren[i].get());
                if (character && !isAirEnemy(character)) {
                    character->setVelocity(0, 0);
                }
            }
            break;
        }
    }
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    // states.transform *= getTransform();
    target.draw(mSprite, states);
}

void Lane::saveCurrent(std::ostream& out) const {
    out << getCategory() << ' ' << mType << ' ' << mSpawnSide << ' '
        << mRandomFactor << '\n';
}

void Lane::saveChildren(std::ostream& out) const {
    Lane* childLane = nullptr;
    for (auto& child : mChildren) {
        if (child->getCategory() == Category::Lane) {
            childLane = dynamic_cast<Lane*>(child.get());
            continue;
        }
        child->save(out);
    }
    out << "-1\n";  // mark end of children

    if (childLane) {
        childLane->save(out);
    } else {
        out << "-2\n";  // mark end of lanes
    }
}

void Lane::loadCurrent(std::istream& in) {
    int spawnSide;
    in >> spawnSide >> mRandomFactor;
    mSpawnSide = static_cast<SpawnSide>(spawnSide);
}

void Lane::loadChildren(std::istream& in, const TextureHolder& textures) {
    int category;
    in >> category;
    while (category != -1) {
        SceneNode::Ptr object(mObjectFactory->createObject(
            in, static_cast<Category::Type>(category)
        ));
        if (object) {
            if (object->getCategory() == Category::TrafficLight) {
                mTrafficLight = dynamic_cast<TrafficLight*>(object.get());
            }
            attachChild(std::move(object));
        }
        in >> category;
    }

    in >> category;
    if (category == -2) {
        return;
    } else {
        int type;
        in >> type;
        SceneNode::Ptr lane(
            std::make_unique<Lane>(in, static_cast<LaneType>(type), textures)
        );
        attachChild(std::move(lane));
    }
}

void createMultipleLanes(
    const TextureHolder& textures, int laneNumber, Lane::Ptr& topLane,
    Lane*& bottomLane, bool isBuffer, float levelScale
) {
    // If these are buffer lanes, then they do not contain river
    int laneTypeCount = LaneType::TypeCount - isBuffer;
    std::cout << laneTypeCount << '\n';

    // Bottom lane
    LaneType randomLaneType = static_cast<LaneType>(rand() % laneTypeCount);
    Lane::Ptr lane(
        std::make_unique<Lane>(randomLaneType, textures, isBuffer, levelScale)
    );

    bottomLane = lane.get();

    while (--laneNumber) {
        // std::cout << "Lane of type " << randomLaneType << " is created\n";
        randomLaneType = static_cast<LaneType>(rand() % laneTypeCount);

        Lane::Ptr parentLane(std::make_unique<Lane>(
            randomLaneType, textures, isBuffer, levelScale
        ));
        parentLane->attachChild(std::move(lane));
        lane = std::move(parentLane);
    }

    topLane = std::move(lane);
}
