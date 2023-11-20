#include "Label.hpp"

#include "Utility.hpp"

Label::Label(
    const std::string& text, const FontHolder& fonts,
    const TextureHolder& textures, int characterSize
)
    : mText(text, fonts.get(Fonts::Main), characterSize),
      mTexture(textures.get(Textures::BackgroundLabel)) {
    mSprite.setTexture(mTexture);

    sf::FloatRect bounds = mSprite.getLocalBounds();
    centerOrigin(mText);
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Label::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}
