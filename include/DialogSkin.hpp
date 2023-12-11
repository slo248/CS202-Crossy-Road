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
    void addSkins(int i, float x, Textures::ID skin, State::Context context);
    Button::Ptr mButtonLeft;
    Button::Ptr mButtonRight;
    std::array<Animation::Ptr, 6> mSkins;
    Animation::Ptr mChosenSkin;
    
};

#endif
