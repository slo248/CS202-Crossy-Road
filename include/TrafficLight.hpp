#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

class TrafficLight : public SceneNode {
   public:
    enum Type { Field, Graveyard, Swamp, TypeCount };
    enum Color { Red, Green, Blue };

   public:
    TrafficLight(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    Color getColor();

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;

   private:
    Type mType;
    sf::Time mElapsedTime;
    sf::Sprite mSprite;
    std::size_t mCurrentFrame;
    std::size_t mNumFrames;
};

#endif  // TRAFFIC_LIGHT_HPP
