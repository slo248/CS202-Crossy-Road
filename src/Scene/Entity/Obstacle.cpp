#include "Obstacle.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

namespace {
const std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(Type type, const TextureHolder& textures, float levelScale)
    : Entity(sf::Vector2f(Table[type].normalSpeed * levelScale, 0)),
      mType(type),
      mSprite(textures.get(Table[type].texture)),
      mIsBlockingPlayer(Table[type].isBlockingPlayer) {
    if (type == Type::River_Log1) {
        setScaleNormalVelocity(1.0);
    }

    // float scaleFactor =
    //     (float)Table[type].textureRect.height /
    //     mSprite.getTextureRect().height;
    // mSprite.scale(scaleFactor, scaleFactor);

    centerOrigin(mSprite);
}

Obstacle::~Obstacle() {
    // switch (mType) {
    //     case Type::Field_Stone6:
    //         std::cout << "Field_Stone6";
    //         break;

    //     case Type::Field_Bush:
    //         std::cout << "Field_Bush";
    //         break;

    //     case Type::Field_Tent:
    //         std::cout << "Field_Tent";
    //         break;

    //     case Type::Field_Tree1:
    //         std::cout << "Field_Tree1";
    //         break;

    //     case Type::Field_Lamp1:
    //         std::cout << "Field_Lamp1";
    //         break;

    //     case Type::Graveyard_House1:
    //         std::cout << "Graveyard_House1";
    //         break;

    //     case Type::Graveyard_Tree2:
    //         std::cout << "Graveyard_Tree2";
    //         break;

    //     case Type::Graveyard_Statue8:
    //         std::cout << "Graveyard_Statue8";
    //         break;

    //     case Type::River_Log1:
    //         std::cout << "River_Log1";
    //         break;
    // }

    // std::cout << " destroyed!\n";
}

unsigned int Obstacle::getCategory() const {
    return mType == River_Log1 ? Category::Decoration : Category::Obstacle;
}

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

sf::FloatRect Obstacle::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

void Obstacle::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // std::cout << "Position" << getWorldPosition().x << " "
    //           << getWorldPosition().y << '\n';
    updateMovementPattern(dt);
    Entity::updateCurrent(dt, commands);
}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void Obstacle::updateMovementPattern(sf::Time dt) {}
