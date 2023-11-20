#ifndef DIALOG_GENERAL_HPP
#define DIALOG_GENERAL_HPP

#include <array>

#include "Button.hpp"
#include "Dialog.hpp"
#include "Label.hpp"
#include "Player.hpp"
#include "State.hpp"

class DialogGeneral : public Dialog {
   public:
    DialogGeneral(const sf::Texture& texture, State::Context context);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void handleEvent(const sf::Event& event);
    void updateLabels();
    void addButtonLabel(
        Player::Action action, float y, Textures::ID Button,
        State::Context context
    );

   private:
    sf::Sprite mLabelTextKeys;
    sf::Sprite mLabelTextSounds;
    std::array<Button::Ptr, Player::Count> mBindingButtons;
    std::array<Label::Ptr, Player::Count> mBindingLabels;
};

#endif
