#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP
#include "State.hpp"
#include "Button.hpp"

class PauseState : public State {
   public:
    PauseState(StateStack& stack, Context context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
