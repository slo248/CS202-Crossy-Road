#ifndef ANIMATION_LIST_HPP
#define ANIMATION_LIST_HPP

#include <vector>

#include "Animation.hpp"

class AnimationList : public sf::Transformable, public sf::Drawable {
   public:
    AnimationList();

    void setRepeat(bool flag);

    bool isInProgress() const;
    bool isRepeated() const;

    void play();
    void stop();

    void update(sf::Time dt);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    int mCurAnimation;
    std::vector<Animation::Ptr> mAnimations;

    bool mRepeat;
};

#endif  // ANIMATION_LIST_HPP
