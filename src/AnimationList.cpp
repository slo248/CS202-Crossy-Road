#include "AnimationList.hpp"

#include <cassert>

AnimationList::AnimationList()
    : mCurAnimation(-1), mAnimations(), mRepeat(false) {}

void AnimationList::setRepeat(bool flag) { mRepeat = flag; }

void AnimationList::add(Animation::Ptr animation) {
    assert(!animation->isRepeated());
    mAnimations.push_back(std::move(animation));
}

bool AnimationList::isInProgress() const { return mCurAnimation != -1; }

bool AnimationList::isRepeated() const { return mRepeat; }

void AnimationList::play() {
    if (isInProgress()) return;
    mCurAnimation = 0;
    mAnimations[mCurAnimation]->play();
}

void AnimationList::stop() {
    if (!isInProgress()) return;
    mAnimations[mCurAnimation]->stop();
    mCurAnimation = -1;
}

void AnimationList::update(sf::Time dt) {
    if (!isInProgress()) return;
    mAnimations[mCurAnimation]->update(dt);
    if (mAnimations[mCurAnimation]->isInProgress()) return;
    mCurAnimation++;
    if (mCurAnimation == mAnimations.size()) {
        if (!isRepeated()) {
            mCurAnimation = -1;
            return;
        } else
            mCurAnimation = 0;
    }
    mAnimations[mCurAnimation]->play();
}

void AnimationList::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    if (!isInProgress()) return;
    states.transform *= getTransform();
    target.draw(*mAnimations[mCurAnimation], states);
}
