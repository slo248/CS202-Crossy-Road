#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP
#include "Button.hpp"
#include "State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context& context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
