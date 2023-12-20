#ifndef CHOOSE_MODE_STATE_HPP
#define CHOOSE_MODE_STATE_HPP

#include "Button.hpp"
#include "State.hpp"

class ChooseModeState : public State {
   public:
    ChooseModeState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    Config::ChooseModeState::Mode mMode;
    sf::Sprite mBackgroundSprite;
};

#endif
