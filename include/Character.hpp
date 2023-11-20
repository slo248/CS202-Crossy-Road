#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Character : public Entity {
   public:
    enum Type {
        Bee,
        Bird,
        Dog,
        Rabbit,
        Sheep,
        Crocodile,
        Frog,
        Turtle,
        BeeBoss,
        BombBat,
        Fishmen,
        Orc,
        Zombie,
        // Callbee,
        // Octopus,
        // Slime,

        Archer,
        Enchantress,
        Knight,
        Musketeer,
        Swordsman,
        Wizard,

        TypeCount
    };

   public:
    Character(Type type, const TextureHolder& textures);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void updateMovementPattern(sf::Time dt);

   private:
    Type mType;
    Animation mAnimation;
};

#endif  // CHARACTER_HPP
