#ifndef LOSE_STATE_HPP
#define LOSE_STATE_HPP

#include "Button.hpp"
#include "State.hpp"
#include "Animation.hpp"

class LoseState : public State {
   public:
    LoseState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDialogDefeat;
    Config::LoseState::Mode mMode;
    Animation::Ptr mPlayerSkin;
};

#endif
