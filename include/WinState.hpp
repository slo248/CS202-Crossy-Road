#ifndef WIN_STATE_HPP
#define WIN_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class WinState : public State {
   public:
    WinState(StateStack& stack, Context& context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDialogVictory;
};

#endif
