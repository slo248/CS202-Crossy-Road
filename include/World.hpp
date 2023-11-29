#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "ResourceIdentifiers.hpp"

class World {
   public:
   private:
    enum Layer { Background, OnGround, Air, LayerCount };

   private:
    TextureHolder& mTextures;
    FontHolder& mFonts;
    sf::RenderWindow& mWindow;

    sf::View mWorldView;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mLayers;

    sf::Vector2f mWorldBounds;
    Character* mPlayer;

    CommandQueue mCommandQueue;
};

#endif
