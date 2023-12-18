#ifndef SETTING_STATE_HPP
#define SETTING_STATE_HPP

#include "Button.hpp"
#include "DialogGeneral.hpp"
#include "DialogSkin.hpp"

class SettingState : public State {
   public:
    SettingState(StateStack& stack, Context& context, int mode = 0);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    bool mIsGeneral;
    sf::Sprite mBackgroundSprite;
    DialogGeneral::Ptr mDialogGeneral;
    Button::Ptr mButtonGeneral;
    DialogSkin::Ptr mDialogSkin;
    Button::Ptr mButtonSkin;
    sf::RenderWindow* mWindow;
};

#endif
