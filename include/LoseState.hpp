#ifndef LOSE_STATE_HPP
#define LOSE_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class LoseState : public State {
   public:
    LoseState(StateStack& stack, Context& context, bool mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDialogDefeat;
};

#endif
