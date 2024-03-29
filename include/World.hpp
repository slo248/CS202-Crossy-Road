#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Config.hpp"
#include "ResourceIdentifiers.hpp"
#include "State.hpp"

class World {
   public:
    World(State::Context& context);

    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    sf::FloatRect getBattlefieldBounds() const;
    int getScore() const;
    Config::Game::Level getGameType() const;

    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;
    void save() const;

   private:
    enum Layer { Background, OnGround, Air, LayerCount };
    const int NUM_LANE = 10;
    const int BUFFER_LANE = 2;
    const float MAXIMUM_DIFFICULTY_FACTOR = 1.6;
    const int MAXIMUM_SCROLL_SPEED = 60;
    const int mTotalBlocks;

    void buildScene();
    void buildLayers();
    void buildBlocks();
    void buildGround();
    void updateDifficulty();
    void removeEntitiesOutsizeView();
    void setDefaultScoreText();
    void updateBoard();
    void makeWeather(int weather = -1);
    void load();

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
    Character* mPlayerSkin;      // Saved independently

    CommandQueue mCommandQueue;
    Config::Game::Level mGameLevel;  // Save

    Lane* mTopLane;     // Saved independently
    int mRemainBlocks;  // Save

    int mPlayerPreRow;        // Save
    int mScores;              // Save
    float mDifficultyFactor;  // Save

    sf::Text mScoreText;
    sf::Text mGameModeText;
    State::Context* mContext;

    Config::Game::Weather mWeather;
    sf::Sprite mWeatherSprite;
};

#endif
