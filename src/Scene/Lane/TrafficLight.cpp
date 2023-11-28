#include "TrafficLight.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#define GREEN_INTERVAL sf::seconds(1.5)
#define YELLOW_INTERVAL sf::seconds(0.5)
#define RED_INTERVAL sf::seconds(2.0)

namespace {
const std::vector<TrafficLightData> Table = initializeTrafficLightData();
}

TrafficLight::TrafficLight(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), Table[type].textureRect),
      mCurrentFrame(0) {}

unsigned int TrafficLight::getCategory() const {
    return Category::TrafficLight;
}

sf::FloatRect TrafficLight::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

sf::FloatRect TrafficLight::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

TrafficLight::Phase TrafficLight::getPhase() { return mPhase; }

TrafficLight::Color TrafficLight::getColor() {
    return static_cast<Color>(mCurrentFrame / 6);
}

void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
    mElapsedTime += dt;

    if (mCurrentFrame < 6 && mElapsedTime >= GREEN_INTERVAL) {
        mElapsedTime -= GREEN_INTERVAL;
        mCurrentFrame = 6;
        mNumFrames = 12;
        mPhase = Phase::GreenToYellow;
    } else if (mCurrentFrame < 12 && mElapsedTime >= YELLOW_INTERVAL) {
        mElapsedTime -= YELLOW_INTERVAL;
        mCurrentFrame = 12;
        mNumFrames = 18;
        mPhase = Phase::YellowToRed;
    } else if (mElapsedTime >= RED_INTERVAL) {
        mElapsedTime -= RED_INTERVAL;
        mCurrentFrame = 0;
        mNumFrames = 6;
        mPhase = Phase::RedToGreen;
    } else {
        mCurrentFrame = (++mCurrentFrame) % mNumFrames;
        mPhase = Phase::InPhase;
    }

    sf::Vector2f spriteSize = mSprite.getLocalBounds().getSize();
    sf::IntRect textureRect = sf::IntRect(
        mCurrentFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y
    );

    mSprite.setTextureRect(textureRect);
}

void TrafficLight::drawCurrent(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    target.draw(mSprite, states);
}
