#ifndef APPLICATION_HPP
#define APPLICATION_HPP

// #include "MusicPlayer.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
// #include "SoundPlayer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "StateStack.hpp"


class Application {
   public:
    Application();
    ~Application();
    void run();

   private:
    void processInput();
    void update(sf::Time dt);
    void render();

    void registerStates();
    State::Context initContext();

   private:
    const sf::Time TimePerFrame = DEFAULT_TIME_PER_FRAME;

    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;
    Player mPlayer;
    std::vector<int> mHighScores;

    // MusicPlayer mMusic;
    // SoundPlayer mSounds;
    StateStack mStateStack;
};

#endif
