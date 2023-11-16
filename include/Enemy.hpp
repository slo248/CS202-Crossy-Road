#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Enemy : public Entity {
   public:
    enum Type {
        // bosses
        BeeBoss,
        BombBat,
        Fishmen,
        Orc,
        Zombie,

        // bombs
        Callbee,
        Octopus,
        Slime,
        FullscreenBlind,
        TypeCount
    };

   public:
    Enemy(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void updateMovementPattern(sf::Time dt);

   private:
    Type mType;
    sf::Sprite mSprite;
};

#endif  // ENEMY_HPP
