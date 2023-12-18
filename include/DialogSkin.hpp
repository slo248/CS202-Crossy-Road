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
    DialogSkin(const sf::Texture& texture, State::Context context);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void handleEvent(const sf::Event& event);
    virtual void update(sf::Time dt) override;

   private:
    int mNumSkins = 6;
    int mCurrentSkin = 0;
    void addSkins(int i, sf::Vector2f position, sf::Vector2i frameSize, Textures::ID skin);
    void addChosenSkins(int i, sf::Vector2f position, sf::Vector2i frameSize, Textures::ID skin);
    void changeSkin(int i);
    Button::Ptr mButtonLeft;
    Button::Ptr mButtonRight;
    std::array<Animation::Ptr, 6> mSkins;
    std::array<Animation::Ptr, 6> mChosenSkins;
    
};

#endif
