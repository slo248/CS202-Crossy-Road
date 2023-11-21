#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.hpp"

class Animation : public sf::Transformable, public sf::Drawable {
   public:
    typedef std::unique_ptr<Animation> Ptr;

   public:
    Animation(const sf::Texture& texture, sf::Vector2i frameSize, int numFrame);

    void setDuration(sf::Time t);
    void setRepeat(bool flag);

    bool isInProgress() const;
    bool isRepeated() const;

    void update(sf::Time dt);
    void play();

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Sprite mSprite;
    sf::IntRect mStartRect;
    sf::Time mElapsedTime;
    sf::Time mDuration;
    int mCurFrame;
    int mNumFrame;
    bool mInProgress;
    bool mRepeat;
};

#endif  // ANIMATION_HPP
