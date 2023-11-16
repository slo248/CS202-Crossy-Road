#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Obstacle : public Entity {
   public:
    enum Type {
        // <-------------------Obstacle----------------->
        // <----------Field---------->
        fence,
        campfire1,
        campfire2,
        pointer1,
        pointer2,
        stone1,
        stone2,
        stone3,
        stone4,
        stone5,
        grass1,
        grass2,
        grass3,
        grass4,
        grass5,
        bush1,
        bush2,
        bush3,
        bush4,
        flower1,
        flower2,
        flower3,
        flower4,
        butterfly1,
        butterfly2,
        butterfly3,
        butterfly4,
        tent,
        tree1,
        tree2,
        log,
        lamp,
        dirt1,
        dirt2,
        dirt3,
        box1,
        box2,
        box3,
        // // <----------Field---------->

        ////////////////////////////////////

        // <-----------Graveyard----------->
        gy_log,
        gy_tree1,
        gy_tree2,
        gy_tree3,
        gy_tree4,
        gy_grass1,
        gy_grass2,
        gy_grass3,
        gy_grass4,
        gy_grass5,
        bone1,
        bone2,
        bone3,
        bone4,
        lantern,
        gy_fence,
        statue1,
        statue2,
        statue3,
        statue4,
        statue5,
        statue6,
        // <----------Graveyard----------->

        ///////////////////////////////////

        // <-----------River-------------->
        rv_grass1,
        rv_grass2,
        rv_grass3,
        rv_grass4,
        rv_grass5,
        rv_stone1,
        rv_stone2,
        rv_stone3,
        rv_stone4,
        rv_stone5,
        jump_log,
        // <-----------River-------------->

        ///////////////////////////////////

        // <----------Swamp--------------->
        sw_tree1,
        sw_tre2,
        torch,
        sw_grass1,
        sw_grass2,
        sw_grass3,
        sw_grass4,
        sw_grass5,
        sw_stone1,
        sw_stone2,
        sw_stone3,
        sw_stone4,
        sw_stone5,
        sw_pointer1,
        sw_pointer2,
        well,
        // <----------Swamp--------------->
        // <-------------------Obstacle----------------->

        TypeCount
    };

   public:
    Obstacle(Type type, const TextureHolder& textures);
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
    bool mIsBlockingPlayer;
    bool mIsHavingMovement;
};

#endif  // OBSTACLE_HPP
