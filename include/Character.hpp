#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "Movement.hpp"
#include "ResourceIdentifiers.hpp"

class Lane;

class Character : public Entity {
   public:
    enum Direction { ToLeft, ToRight, ToUpper, ToLower };

    enum Type {
        Bee,
        Bird,
        Crocodile,
        Dog,
        Frog,
        Rabbit,
        Sheep,
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
    Character(
        Type type, const TextureHolder& textures,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    ~Character();
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Type getType() const;
    void moveCharacter(Direction direction);

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void updateMovementPattern(sf::Time dt);

   private:
    Type mType;
    std::vector<Animation> mAnimations;
    Animation* mCurrentAnimation;
    Movement mMovement;
    Lane* mCurrentLane;
};

#endif  // CHARACTER_HPP
