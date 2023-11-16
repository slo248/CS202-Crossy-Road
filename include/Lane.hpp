#ifndef LANE_HPP
#define LANE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "TrafficLight.hpp"

class Lane : public SceneNode {
   public:
    enum Type { River, Dirt, Grass, Graveyard, Soil, Swamp, TypeCount };

   public:
    // explicit Lane(Type type, const sf::Texture& texture);
    // Lane(
    //     Type type, const sf::Texture& texture, const sf::IntRect& textureRect
    // );
    Lane(Type type, const TextureHolder& textures);

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void updateMovementPattern(sf::Time dt);

   private:
    Type mType;
    sf::Sprite mSprite;
    Lane *mTopLane, *mBottomLane;
    bool mIsForDecoration;
};

#endif  // LANE_HPP
