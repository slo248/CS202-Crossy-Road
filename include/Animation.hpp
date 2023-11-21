#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.hpp"

class Animation : public sf::Transformable, public sf::Drawable {
   public:
    typedef std::unique_ptr<Animation> Ptr;

   public:
    Animation(const sf::Texture& texture, sf::Vector2i frameSize, int numFrame);

    void setRepeat(bool flag);
    void setDuration(sf::Time t);
    void setTimePerFrame(sf::Time t);

    bool isInProgress() const;
    bool isRepeated() const;

    void update(sf::Time dt);
    void play();
    void stop();

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Sprite mSprite;
    sf::IntRect mStartRect;
    sf::Time mElapsedTime;
    sf::Time mTotalElapsedTime;
    sf::Time mDuration;
    sf::Time mTimePerFrame;
    int mCurFrame;
    int mNumFrame;
    bool mInProgress;
    bool mRepeat;
};

#endif  // ANIMATION_HPP
