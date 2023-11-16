#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

class TrafficLight : public SceneNode {
   public:
    enum Type { Field, Graveyard, Swamp, TypeCount };
    TrafficLight(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void updateMovementPattern(sf::Time dt);

   private:
    sf::Sprite mSprite;
    Type mType;
    int mColor;
    sf::Time mTime;
};

#endif  // TRAFFIC_LIGHT_HPP
