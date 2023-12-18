#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include "Button.hpp"
#include "Label.hpp"
#include "State.hpp"

class LevelState : public State {
   public:
    LevelState(StateStack& stack, Context& context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackground;
    void addButtonLevel(State::Context& context, const int& numLevel);
};

#endif
