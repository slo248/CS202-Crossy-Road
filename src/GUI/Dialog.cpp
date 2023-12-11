#include "Dialog.hpp"

Dialog::Dialog(const sf::Texture& texture, State::Context context)
    : mGUIContainer(), mTexture(texture), mContext(context) {
    mSprite.setTexture(mTexture);

    sf::FloatRect bounds = mSprite.getLocalBounds();
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
