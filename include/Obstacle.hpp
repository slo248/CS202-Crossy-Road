#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Obstacle : public Entity {
   public:
    enum Type {
        // <-------------------Obstacle----------------->
        // <----------Field---------->
        Field_Stone6,
        Field_Bush,
        Field_Tent,
        Field_Tree1,
        Field_Lamp1,
        // // <----------Field---------->

        ////////////////////////////////////

        // <-----------Graveyard----------->
        Graveyard_House1,
        Graveyard_Tree2,
        Graveyard_Statue8,
        // <----------Graveyard----------->

        ///////////////////////////////////

        // <-----------River-------------->
        River_Log1,
        // <-----------River-------------->

        ///////////////////////////////////

        // <----------Swamp--------------->
        Swamp_Tree2,
        Swamp_House1,
        Swamp_Well1,
        // <----------Swamp--------------->
        // <-------------------Obstacle----------------->

        TypeCount
    };

   public:
    Obstacle(Type type, const TextureHolder& textures, float levelScale);
    Obstacle(
        std::istream& in, Type type, const TextureHolder& textures,
        float levelScale
    );
    ~Obstacle();
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual sf::FloatRect getLocalBounds() const override;

   private:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void updateMovementPattern(sf::Time dt);

    virtual void saveCurrent(std::ostream& out) const override;
    virtual void loadCurrent(std::istream& in) override;

   private:
    Type mType;          // Save
    sf::Sprite mSprite;  // Type-dependent
};

#endif  // OBSTACLE_HPP
