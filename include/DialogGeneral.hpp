#ifndef DIALOG_GENERAL_HPP
#define DIALOG_GENERAL_HPP

#include <array>

#include "Button.hpp"
#include "Dialog.hpp"
#include "Label.hpp"
#include "Player.hpp"
#include "State.hpp"
#include "VolumeBar.hpp"

class DialogGeneral : public Dialog {
   public:
    DialogGeneral(const sf::Texture& texture, State::Context& context);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    virtual void handleEvent(const sf::Event& event);

   private:
    void updateLabels();
    void addButtonLabel(Player::Action action, float y, Textures::ID Button);
    void addListMusic();

   private:
    sf::Sprite mLabelTextKeys;
    sf::Sprite mLabelTextSounds;
    VolumeBar mVolumeBar;
    std::array<Button::Ptr, Player::Count> mBindingButtons;
    std::array<Label::Ptr, Player::Count> mBindingLabels;
    std::array<Button::Ptr, Musics::MusicCount - 1> mListMusics;
    Button::Ptr mChosenMusic;

    int volume = 50;
    bool isChoosingMusic = false;
};

#endif
