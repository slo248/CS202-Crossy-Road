#ifndef SETTING_STATE_HPP
#define SETTING_STATE_HPP

#include "Button.hpp"
#include "DialogGeneral.hpp"
#include "DialogSkin.hpp"

class SettingState : public State {
   public:
    SettingState(StateStack& stack, Context& context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    DialogGeneral::Ptr mDialogGeneral;
    Button::Ptr mButtonGeneral;
    DialogSkin::Ptr mDialogSkin;
    Button::Ptr mButtonSkin;
    sf::RenderWindow* mWindow;
    Config::SettingState::Mode mMode;
    bool mChangeableSkin;
};

#endif
