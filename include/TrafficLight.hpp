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
    explicit TrafficLight(
        std::istream& in, Type type, const TextureHolder& textures
    );

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Phase getPhase();
    Color getColor();

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;

    virtual void saveCurrent(std::ostream& out) const override;
    virtual void loadCurrent(std::istream& in) override;

   private:
    Type mType;                 // Save
    Phase mPhase;               // Save
    Color mColor;               // Save
    sf::Time mElapsedTime;      // Save
    sf::Sprite mSprite;         // Type-dependent
    std::size_t mCurrentFrame;  // Type-dependent
    std::size_t mNumFrames;     // Type-dependent
};

#endif  // TRAFFIC_LIGHT_HPP
