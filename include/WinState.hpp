#ifndef WIN_STATE_HPP
#define WIN_STATE_HPP

#include "Animation.hpp"
#include "Button.hpp"
#include "GameState.hpp"
#include "State.hpp"

class WinState : public State {
   public:
    WinState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    Animation::Ptr mPlayerSkin;
    Config::WinState::Mode mMode;
    sf::Sprite mBackgroundSprite;
    sf::Sprite mDialogVictory;
};

#endif
