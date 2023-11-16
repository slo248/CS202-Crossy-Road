#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Animal : public Entity {
   public:
    enum Type {
        Bee,
        Bird1,
        Bird2,
        Bird3,
        Bird4,
        Dog,
        Rabbit,
        Sheep,
        Crocodile,
        Frog,
        Turtle,
        TypeCount
    };

   public:
    Animal(Type type, const TextureHolder& textures);
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

#endif  // ANIMAL_HPP
