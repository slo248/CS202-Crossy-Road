#include "Animation.hpp"

#include "Utility.hpp"

Animation::Animation(
    const sf::Texture& texture, sf::Vector2i frameSize, int numFrame
)
    : mSprite(texture),
      mStartRect(0, 0, frameSize.x, frameSize.y),
      mNumFrame(numFrame),
      mCurFrame(0),
      mElapsedTime(sf::Time::Zero),
      mDuration(sf::seconds(1)),
      mInProgress(false),
      mRepeat(false) {}

void Animation::setDuration(sf::Time t) { mDuration = t; }

void Animation::setRepeat(bool flag) { mRepeat = flag; }

bool Animation::isInProgress() const { return mInProgress; }

bool Animation::isRepeated() const { return mRepeat; }

void Animation::update(sf::Time dt) {
    if (!isInProgress()) return;

    mElapsedTime += dt;

    sf::Time timePerFrame = mDuration / (1.f * mNumFrame);
    sf::Vector2i textureBound(mSprite.getTexture()->getSize());
    sf::IntRect textureRect(mSprite.getTextureRect());

    while (mElapsedTime >= timePerFrame) {
        mElapsedTime -= timePerFrame;
        mCurFrame++;
        if (mCurFrame == mNumFrame) {
            if (!isRepeated()) {
                mInProgress = false;
                return;
            }
            mCurFrame = 0;
            textureRect = mStartRect;
            continue;
        }

        textureRect.left += textureRect.width;
        if (textureRect.left >= textureBound.x) {
            textureRect.left = 0;
            textureRect.top += textureRect.height;
            if (textureRect.top >= textureBound.y) textureRect.top = 0;
        }
    }

    mSprite.setTextureRect(textureRect);
}

void Animation::play() {
    if (isInProgress()) return;
    mInProgress = true;
    mCurFrame = 0;
    mElapsedTime = sf::Time::Zero;
    mSprite.setTextureRect(mStartRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isInProgress()) return;
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
