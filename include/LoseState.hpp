#ifndef LOSE_STATE_HPP
#define LOSE_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class LoseState : public State {
   public:
    enum Mode {};

    LoseState(StateStack& stack, Context& context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDialogDefeat;
    Mode mMode;
};

#endif
