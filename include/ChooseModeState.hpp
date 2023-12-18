#ifndef CHOOSE_MODE_STATE_HPP
#define CHOOSE_MODE_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class ChooseModeState : public State {
   public:
    enum Mode { Play, Continue };

    ChooseModeState(StateStack& stack, Context& context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    Mode mMode;
    sf::Sprite mBackgroundSprite;
};

#endif
