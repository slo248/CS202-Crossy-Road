#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "MusicPlayer.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SoundEffectPlayer.hpp"
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
    MusicPlayer mMusics;
    SoundEffectPlayer mSoundEffects;
    Player mPlayer;
    std::vector<Highscore> mHighScores;
    StateStack mStateStack;
};

#endif
