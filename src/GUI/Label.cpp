#include "Label.hpp"

#include "Utility.hpp"

Label::Label(
    const std::string& text, Fonts::ID font, State::Context context,
    int characterSize
)
    : mText(text, context.fonts->get(font), characterSize) {}

void Label::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}
