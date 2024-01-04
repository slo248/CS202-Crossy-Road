#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Config.hpp"
#include "ResourceIdentifiers.hpp"

class World {
   public:
    World(
        TextureHolder& textures, FontHolder& fonts, sf::RenderWindow& window,
        Config::GameLevel::Type gameType, bool isLoadedFromFile = false
    );

    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    sf::FloatRect getBattlefieldBounds() const;

    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;
    void saveCurrentGame() const;

   private:
    enum Layer { Background, OnGround, Air, LayerCount };
    const int NUM_LANE = 10;
    const int BUFFER_LANE = 2;
    const int mTotalBlocks;

    void buildScene();
    void buildBlocks();
    void buildLayers();
    void removeEntitiesOutsizeView();
    void setDefaultScoreText();
    void loadGame();
    void updateBoard();

   private:
    TextureHolder& mTextures;
    FontHolder& mFonts;
    sf::RenderWindow& mWindow;

    sf::View mWorldView;
    sf::Vector2f mScrollSpeed;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mLayers;
    // Above are all type-dependent

    sf::FloatRect mWorldBounds;  // Type-dependent
    Character* mPlayer;          // Saved independently

    CommandQueue mCommandQueue;
    Config::GameLevel::Type mGameType;  // Save

    Lane* mTopLane;     // Saved independently
    int mRemainBlocks;  // Save

    int mPlayerPreRow;  // Save
    int mScores;        // Save

    sf::Text mScoreText;
    sf::Text mGameModeText;
};

#endif
