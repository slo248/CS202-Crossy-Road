#ifndef VOLUME_BAR_HPP
#define VOLUME_BAR_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"

class VolumeBar : public sf::Drawable {
   public:
    VolumeBar(State::Context& Context);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleEvent(sf::RenderWindow& window, sf::Event event);
    void update();
    float getVolumeLevel() { return mVolumeLevel; }

   private:
    float clamp(float value, float min, float max);

   private:
    sf::RectangleShape mVolumeBackground;
    sf::RectangleShape mVolumeBar;
    sf::CircleShape mVolumeDot;
    bool isDragging;
    float mVolumeLevel;
    State::Context* mContext;
};

#endif /* VOLUME_BAR_HPP */
