#include "Label.hpp"

#include "Utility.hpp"

Label::Label(
    const std::string& text, Fonts::ID font, State::Context context,
    int characterSize
)
    : mText(text, context.fonts->get(font), characterSize) {
    sf::FloatRect bounds = mSprite.getLocalBounds();
    centerOrigin<sf::Text>(mText);
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}

void Label::setColor(const std::string& hexCode) {
    unsigned int r, g, b;
    sscanf(hexCode.c_str(), "#%02x%02x%02x", &r, &g, &b);
    mText.setFillColor(sf::Color(r, g, b));
}
