#ifndef SAVED_STATE_HPP
#define SAVED_STATE_HPP
#include "Button.hpp"
#include "State.hpp"

class SavedState : public State {
   public:
    SavedState(StateStack& stack, Context context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
};

#endif
