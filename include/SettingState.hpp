#ifndef SETTING_STATE_HPP
#define SETTING_STATE_HPP

#include <SFML/Graphics.hpp>
#include <array>

#include "DialogGeneral.hpp"
#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Player.hpp"
#include "State.hpp"

// Forward declaration
class Player;
//

class SettingState : public State {
   public:
    SettingState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt) { return true; }
    virtual bool handleEvent(const sf::Event& event) { return true;}

   private:
    void updateLabels();
    void addAButtonLabel(
        Player::Action action, float y, const sf::Texture& mNormal,
        Context context
    );
    void addButtons();
    void addLabels();

   private:
    sf::Sprite mBackgroundSprite;
    // DialogGeneral DialogGeneral;
    // std::array<Button::Ptr, Player::ActionCount> mBindingButtons;
    // std::array<Label::Ptr, Player::ActionCount> mBindingLabels;
};

#endif  // BOOK_SettingSTATE_HPP
