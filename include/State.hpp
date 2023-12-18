#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#include "Container.hpp"
#include "ResourceIdentifiers.hpp"
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
            FontHolder& fonts, Player& player, std::vector<int>& highScores
        );

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
        std::vector<int>* highScores;
        GameState* gameState = nullptr;
        int mode = 0;
        bool isLoadedFromFile = false;
    };

   public:
    State(StateStack& stack, Context& context, int mode = 0);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

   protected:
    int mMode;
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
