#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

class TrafficLight : public SceneNode {
   public:
    enum Type { Field, Graveyard, Swamp, TypeCount };
    enum Phase { RedToGreen, GreenToYellow, YellowToRed, InPhase };
    enum Color { Green, Yellow, Red };

   public:
    TrafficLight(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Phase getPhase();
    Color getColor();

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;

   private:
    Type mType;    // Save
    Phase mPhase;  // Save
    sf::Sprite mSprite;
    sf::Time mElapsedTime;
    std::size_t mCurrentFrame;
    std::size_t mNumFrames;
    Color mColor;  // Save
};

#endif  // TRAFFIC_LIGHT_HPP
