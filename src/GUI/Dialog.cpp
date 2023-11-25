#include "Dialog.hpp"

#include "Utility.hpp"

Dialog::Dialog(
    const std::string& text, const FontHolder& fonts,
    const TextureHolder& textures, int characterSize
)
    : mText(text, fonts.get(Fonts::Main), characterSize),
      mTexture(textures.get(Textures::DialogBackground)) {
    mSprite.setTexture(mTexture);

    sf::FloatRect bounds = mSprite.getLocalBounds();
    centerOrigin<sf::Text>(mText);
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mGUIContainer, states);
    target.draw(mSprite, states);
}
