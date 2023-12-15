#include "TrafficLight.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "Category.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#define GREEN_INTERVAL sf::seconds(5.0)
#define YELLOW_INTERVAL sf::seconds(2.0)
#define RED_INTERVAL sf::seconds(5.0)

namespace {
const std::vector<TrafficLightData> Table = initializeTrafficLightData();
}

TrafficLight::TrafficLight(Type type, const TextureHolder& textures)
    : mType(type),
      mSprite(textures.get(Table[type].texture), sf::IntRect(0, 0, 32, 64)),
      mCurrentFrame(0),
      mNumFrames(6),
      mElapsedTime(sf::Time::Zero),
      mColor(static_cast<Color>(rand() % 3)),
      mPhase(InPhase) {
    centerOrigin(mSprite);
}

/* problem */
TrafficLight::TrafficLight(
    std::istream& in, Type type, const TextureHolder& textures
)
    : mType(type),
      mSprite(textures.get(Table[type].texture), sf::IntRect(0, 0, 32, 64)),
      mCurrentFrame(0),
      mNumFrames(6) {
    loadCurrent(in);
    centerOrigin(mSprite);
    // move(0, -30);
}

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

TrafficLight::Color TrafficLight::getColor() { return mColor; }

void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
    mElapsedTime += dt;

    switch (mColor) {
        case Green: {
            if (mElapsedTime >= GREEN_INTERVAL) {
                mElapsedTime -= GREEN_INTERVAL;
                mPhase = GreenToYellow;
                mColor = Yellow;
            } else {
                mPhase = InPhase;
            }
            break;
        }

        case Yellow: {
            if (mElapsedTime >= YELLOW_INTERVAL) {
                mElapsedTime -= YELLOW_INTERVAL;
                mPhase = YellowToRed;
                mColor = Red;
            } else {
                mPhase = InPhase;
            }
            break;
        }

        case Red: {
            if (mElapsedTime >= RED_INTERVAL) {
                mElapsedTime -= RED_INTERVAL;
                mPhase = RedToGreen;
                mColor = Green;
            } else {
                mPhase = InPhase;
            }
            break;
        }
    }

    // The important thing is the range of mElapsedTime, if the range is too
    // small, we need to multiply it by a bigger number, then mod it by a
    // appropriate number to get the frequency we want
    int tmp = mElapsedTime.asSeconds() * 60;

    if (tmp % 10 == 0) {
        // std::cout << tmp << '\n';
        mCurrentFrame = (++mCurrentFrame) % mNumFrames;
    }

    sf::Vector2f spriteSize = mSprite.getLocalBounds().getSize();
    sf::IntRect textureRect =
        sf::IntRect((6 * mColor + mCurrentFrame) * 32, 0, 32, 64);

    mSprite.setTextureRect(textureRect);
}

void TrafficLight::drawCurrent(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    target.draw(mSprite, states);
}

void TrafficLight::saveCurrent(std::ostream& out) const {
    out << getCategory() << ' ' << mType << ' ' << mPhase << ' ' << mColor
        << ' ' << mElapsedTime.asSeconds() << ' '
        << positionToSlot(getPosition().x) << '\n';
}

void TrafficLight::loadCurrent(std::istream& in) {
    int phase, color, slot;
    float elapsedTime;
    in >> phase >> color >> elapsedTime >> slot;

    mPhase = static_cast<Phase>(phase);
    mColor = static_cast<Color>(color);
    mElapsedTime = sf::seconds(elapsedTime);
    setPosition(slotToPosition(slot), 0);
}
