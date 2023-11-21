#include "AnimationList.hpp"

AnimationList::AnimationList()
    : mCurAnimation(-1), mAnimations(), mRepeat(false) {}

void AnimationList::setRepeat(bool flag) { mRepeat = true; }

bool AnimationList::isInProgress() const { return mCurAnimation != -1; }

bool AnimationList::isRepeated() const { return mRepeat; }

void AnimationList::play() {
    if (isInProgress()) return;
    mCurAnimation = 0;
}

void AnimationList::stop() { mCurAnimation = -1; }

void AnimationList::update(sf::Time dt) {
    if (!isInProgress()) return;
    mAnimations[mCurAnimation]->update(dt);
    if (mAnimations[mCurAnimation]->isInProgress()) return;
    mCurAnimation++;
    if (mCurAnimation == mAnimations.size()) {
        if (!isRepeated())
            mCurAnimation = -1;
        else
            mCurAnimation = 0;
    }
}

void AnimationList::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    if (!isInProgress()) return;
    states.transform *= getTransform();
    target.draw(*mAnimations[mCurAnimation], states);
}
