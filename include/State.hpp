#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Config.hpp"
#include "Container.hpp"
#include "ResourceIdentifiers.hpp"
#include "MusicPlayer.hpp"
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
            FontHolder& fonts, MusicPlayer& musics, Player& player, std::vector<int>& highScores,
            int playerSkinNumber = 0
        );

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        MusicPlayer* musics;
        Player* player;
        std::vector<int>* highScores;
        GameState* gameState = nullptr;
        Config::GameLevel::Type gameLevel;
        int mode = 0;
        int playerSkinNumber;
        bool isLoadedFromFile = false;
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
