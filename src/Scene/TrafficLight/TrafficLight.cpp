#include "TrafficLight.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"

namespace {
const std::vector<TrafficLightData> Table = initializeTrafficLightData();
}

TrafficLight::TrafficLight(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect) {}

unsigned int TrafficLight::getCategory() const {
    return Category::TrafficLight;
}

sf::FloatRect TrafficLight::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
    ;
}

void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {}

void TrafficLight::drawCurrent(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    target.draw(mSprite, states);
}

void TrafficLight::updateMovementPattern(sf::Time dt) {}
