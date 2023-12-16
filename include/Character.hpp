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
        // Bee,
        // Bird,
        Crocodile,
        Dog,
        // Frog,
        // Rabbit,
        // Sheep,
        // Turtle,
        BeeBoss,
        BombBat,
        Fishmen,
        Orc,
        Zombie,
        Wraith,
        WraithPro,
        WraithSwamp,
        GolemGy,
        GolemSwamp,
        Golem,
        SatyrGy,
        SatyrSwamp,
        Satyr,
        MinoGy,
        MinoSwamp,
        Mino,

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
    typedef std::unique_ptr<Character> Ptr;

    Character(
        Type type, const TextureHolder& textures,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    explicit Character(
        std::istream& in, Type type, const TextureHolder& textures,
        float levelScale = LEVEL_ONE_COEFFICIENT
    );
    ~Character();

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    Type getType() const;

    void moveCharacter(Direction direction);
    bool isMarkedForRemoval() const override;
    void setCurrentLane(Lane* lane);
    bool isInMovement() const;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void updateMovementPattern(sf::Time dt);

    virtual void saveCurrent(std::ostream& out) const override;
    virtual void loadCurrent(std::istream& in) override;

   private:
    Type mType;                          // Save
    std::vector<Animation> mAnimations;  // Type-dependent
    Animation* mCurrentAnimation;        // Type-dependent
    Movement mMovement;                  // Type-dependent
    Lane* mCurrentLane;                  // Position-dependent
    bool mIsInMovement;                  // Player-dependent -> no need to save
};

#endif  // CHARACTER_HPP
