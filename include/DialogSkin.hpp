#ifndef DIALOG_SKIN_HPP
#define DIALOG_SKIN_HPP

#include <array>

#include "Animation.hpp"
#include "Button.hpp"
#include "Dialog.hpp"
#include "Label.hpp"
#include "State.hpp"

class DialogSkin : public Dialog {
   public:
    DialogSkin(const sf::Texture& texture, State::Context& context);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    virtual void handleEvent(const sf::Event& event);
    virtual void update(sf::Time dt) override;

   private:
    void addSkins(
        int skinNumber, sf::Vector2f position, sf::Vector2i frameSize,
        Textures::ID skin
    );
    void addChosenSkins(
        int skinNumber, sf::Vector2f position, sf::Vector2i frameSize,
        Textures::ID skin
    );
    void changeSkin(int skinNumber);

   private:
    std::array<Animation::Ptr, NUMBER_OF_SKINS> mSkins;
    std::array<Animation::Ptr, NUMBER_OF_SKINS> mChosenSkins;
    Dialog::Ptr mDialogSuccess;
    const int mNumSkins = NUMBER_OF_SKINS;
    int mCurrentSkin;
};

#endif
