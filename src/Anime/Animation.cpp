#include "Animation.hpp"

#include "Utility.hpp"

Animation::Animation(
    const sf::Texture& texture, sf::Vector2i frameSize, int numFrame, bool isTransparent
)
    : mSprite(texture),
      mStartRect(0, 0, frameSize.x, frameSize.y),
      mNumFrame(numFrame),
      mCurFrame(0),
      mElapsedTime(sf::Time::Zero),
      mTotalElapsedTime(sf::Time::Zero),
      mDuration(sf::seconds(1.5)),
      mInProgress(false),
      mRepeat(false) {
    mTimePerFrame = sf::seconds(mDuration.asSeconds() / mNumFrame + 0.1);
    // std::cout << mTimePerFrame.asSeconds() << std::endl;
    if (isTransparent) {
        mSprite.setColor(sf::Color(255, 255, 255, 128));
    }
}

void Animation::setDuration(sf::Time t) {
    mDuration = t;
    mTimePerFrame = mDuration / (1.f * mNumFrame);
}

void Animation::setTimePerFrame(sf::Time t) { mTimePerFrame = t; }

void Animation::setRepeat(bool flag) { mRepeat = flag; }

bool Animation::isInProgress() const { return mInProgress; }

bool Animation::isRepeated() const { return mRepeat; }

void Animation::update(sf::Time dt) {
    if (!isInProgress()) return;

    mElapsedTime += dt;
    mTotalElapsedTime += dt;

    if (mTotalElapsedTime >= mDuration) {
        if (!isRepeated()) {
            mInProgress = false;
            return;
        }
        float a = mTotalElapsedTime.asSeconds();
        float b = mDuration.asSeconds();
        mTotalElapsedTime = sf::seconds(a - (int(a / b)) * b);
    }

    sf::Vector2i textureBound(mSprite.getTexture()->getSize());
    sf::IntRect textureRect(mSprite.getTextureRect());

    while (mElapsedTime >= mTimePerFrame) {
        mElapsedTime -= mTimePerFrame;
        mCurFrame++;
        if (mCurFrame == mNumFrame) {
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
    centerOrigin(mSprite);
}

void Animation::play() {
    if (isInProgress()) return;
    mInProgress = true;
    mCurFrame = 0;
    mElapsedTime = mTotalElapsedTime = sf::Time::Zero;
    mSprite.setTextureRect(mStartRect);
}

void Animation::stop() {
    if (!isInProgress()) return;
    mInProgress = false;
}

sf::FloatRect Animation::getGlobalBounds() const {
    return mSprite.getGlobalBounds();
}

sf::FloatRect Animation::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isInProgress()) return;
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
