#ifndef VOLUME_BAR_HPP
#define VOLUME_BAR_HPP

#include <SFML/Graphics.hpp>

#include "Component.hpp"
#include "State.hpp"

class VolumeBar : public Component {
   public:
    enum Type { Music, Sfx };
    typedef std::shared_ptr<VolumeBar> Ptr;

    VolumeBar(State::Context& Context, float x, float y, Type type = Music);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
    float getVolumeLevel() { return mVolumeLevel; }

    void handleEvent(const sf::Event& event) override;
    void toggleMute();

   private:
    float clamp(float value, float min, float max);

   private:
    sf::RectangleShape mVolumeBackground;
    sf::RectangleShape mVolumeBar;
    sf::CircleShape mVolumeDot;
    State::Context* mContext;
    Type mType;
    float mVolumeLevel;
    float mX;
    float mY;
    bool mIsDragging;
};

#endif  // VOLUME_BAR_HPP
