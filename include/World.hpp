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
        Config::GameLevel::Type gameType
    );
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    sf::FloatRect getBattlefieldBounds() const;

    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;

   private:
    enum Layer { Background, OnGround, Air, LayerCount };
    const int NUM_LANE = 10;
    const int BUFFER_LANE = 2;

    void buildScene();
    void buildBlocks();
    void removeEntitiesOutsizeView();

   private:
    TextureHolder& mTextures;
    FontHolder& mFonts;
    sf::RenderWindow& mWindow;

    sf::View mWorldView;
    sf::Vector2f mScrollSpeed;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mLayers;

    sf::FloatRect mWorldBounds;
    Character* mPlayer;

    CommandQueue mCommandQueue;
    Config::GameLevel::Type mGameType;  // Save

    Lane* mTopLane;
    int mRemainBlocks;  // Save

    int mPlayerPreRow;  // Save
    int mScores;        // Save

    sf::Text mScoreText;
};

#endif
