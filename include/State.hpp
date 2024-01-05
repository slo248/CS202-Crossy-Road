#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Config.hpp"
#include "Container.hpp"
#include "MusicPlayer.hpp"
#include "ResourceIdentifiers.hpp"
#include "SoundEffectPlayer.hpp"
#include "StateID.hpp"

// Forward declaration
class StateStack;
class Player;
class GameState;
//

class State {
   public:
    typedef std::unique_ptr<State> Ptr;
    struct Context {
        Context(
            sf::RenderWindow& window, TextureHolder& textures,
            FontHolder& fonts, MusicPlayer& musics,
            SoundEffectPlayer& soundEffects, Player& player,
            std::vector<Highscore>& highScores
        );

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        MusicPlayer* musics;
        SoundEffectPlayer* soundEffects;
        Player* player;
        std::vector<Highscore>* highScores;
        GameState* gameState = nullptr;
        Config::Game::Level gameLevel;

        Musics::ID currentMusic = Musics::Music1;
        float volumeMusic = 50;
        float volumeSfx = 50;
        int mode = 0;
        int playerSkinNumber = 0;
        bool isLoadedFromFile = false;
        bool isMuteMusic = false;
        bool isMuteSfx = false;
    };

   public:
    State(StateStack& stack, Context& context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

   protected:
    Context* mContext;
    Container mGUIContainer;

   protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStackClear();

   private:
    StateStack* mStack;
};

#endif
