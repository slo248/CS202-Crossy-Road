#ifndef CREDIT_STATE_HPP
#define CREDIT_STATE_HPP

#include <SFML/Graphics.hpp>

#include "Button.hpp"
#include "State.hpp"

class CreditState : public State {
   public:
    CreditState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    std::shared_ptr<Button> backButton;
};

#endif
