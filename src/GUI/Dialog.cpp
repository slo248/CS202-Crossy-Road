#include "Dialog.hpp"

#include "Utility.hpp"

Dialog::Dialog(
    const sf::Texture& texture
)
    : mTexture(texture) {
    mSprite.setTexture(mTexture);

    sf::FloatRect bounds = mSprite.getLocalBounds();
    centerOrigin(mText);
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}
