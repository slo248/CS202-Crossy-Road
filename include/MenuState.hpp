#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
