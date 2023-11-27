#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Container.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateID.hpp"

// Forward declaration
class StateStack;
class Player;
//

class State {
   public:
    typedef std::unique_ptr<State> Ptr;
    struct Context {
        Context(
            sf::RenderWindow& window, TextureHolder& textures,
            FontHolder& fonts, Player& player
        );
        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

   public:
    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

   protected:
    Container mGUIContainer;
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const;

   private:
    StateStack* mStack;
    Context mContext;
};

#endif
