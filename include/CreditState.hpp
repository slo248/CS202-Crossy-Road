#ifndef CREDIT_STATE_HPP
#define CREDIT_STATE_HPP


#include "Button.hpp"
#include "State.hpp"

class CreditState : public State {
   public:
    CreditState(StateStack& stack, Context& context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
};

#endif
