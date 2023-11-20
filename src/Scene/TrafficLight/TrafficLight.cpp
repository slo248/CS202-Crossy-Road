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

sf::FloatRect TrafficLight::getBoundingRect() const {}

TrafficLight::Color TrafficLight::getColor() {
    return static_cast<Color>(mCurrentFrame);
}

void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
    mElapsedTime += dt;

    switch (mCurrentFrame) {
        case 0: {
            if (mElapsedTime >= GREEN_INTERVAL) {
                mElapsedTime -= GREEN_INTERVAL;
                mCurrentFrame = 6;
                mNumFrames = 12;
            }
            break;
        }

        case 6: {
            if (mElapsedTime >= YELLOW_INTERVAL) {
                mElapsedTime -= YELLOW_INTERVAL;
                mCurrentFrame = 12;
                mNumFrames = 18;
            }
            break;
        }

        case 12: {
            if (mElapsedTime >= RED_INTERVAL) {
                mElapsedTime -= RED_INTERVAL;
                mCurrentFrame = 0;
                mNumFrames = 6;
            }
            break;
        }

        default: {
            mCurrentFrame = (++mCurrentFrame) % mNumFrames;
        }
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
