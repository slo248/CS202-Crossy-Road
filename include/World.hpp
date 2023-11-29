#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Config.hpp"
#include "ResourceIdentifiers.hpp"

class World {
   public:
    World(
        TextureHolder& textures, FontHolder& fonts, sf::RenderWindow& window,
        Config::GameType gameType
    );
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    sf::FloatRect getViewBounds() const;

   private:
    enum Layer { Background, OnGround, Air, LayerCount };

    void buildScene();
    void removeEntitiesOutsizeView();

   private:
    TextureHolder& mTextures;
    FontHolder& mFonts;
    sf::RenderWindow& mWindow;

    sf::View mWorldView;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mLayers;

    sf::FloatRect mWorldBounds;
    Character* mPlayer;

    CommandQueue mCommandQueue;
    Config::GameType mGameType;
};

#endif
