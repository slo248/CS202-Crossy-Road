#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.hpp"

class Animation : public sf::Transformable, public sf::Drawable {
   public:
    Animation(const sf::Texture& texture);

    void setRepeat(bool flag);
    void setFrameSize(sf::Vector2i size);
    void setDuration(sf::Time t);

    bool isInProgress() const;
    bool isRepeated() const;

    void update(sf::Time dt);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Sprite mSprite;
    sf::Vector2i mFrameSize;
    sf::Time mElaspedTime;
    sf::Time mDuration;
    int mCurFrame;
    int mNumFrame;
    bool mInProgress;
    bool mRepeat;
};

#endif  // ANIMATION_HPP
