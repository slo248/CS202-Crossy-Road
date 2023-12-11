#ifndef SETTING_STATE_HPP
#define SETTING_STATE_HPP

#include "Button.hpp"
#include "DialogGeneral.hpp"

class SettingState : public State {
   public:
    SettingState(StateStack& stack, Context context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
};

#endif  // BOOK_SettingSTATE_HPP
