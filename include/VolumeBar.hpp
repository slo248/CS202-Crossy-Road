#ifndef VOLUME_BAR_HPP
#define VOLUME_BAR_HPP

#include <SFML/Graphics.hpp>

class VolumeBar : public sf::Drawable {
public:
    VolumeBar(float width, float height);
    void setPosition(float x, float y);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleEvent(sf::RenderWindow& window, sf::Event event);
    void update();
    float getVolumeLevel() { return volumeLevel; }

private:
    sf::RectangleShape volumeBar;
    sf::CircleShape volumeDot;
    bool isDragging;
    float volumeLevel;

    float clamp(float value, float min, float max);
};

#endif /* VOLUME_BAR_HPP */
