#include "Label.hpp"

#include "Utility.hpp"

Label::Label(
    const std::string& text, Fonts::ID font, State::Context& context,
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

void Label::setColor(const std::string& hexCode) {
    unsigned int r, g, b;
    sscanf(hexCode.c_str(), "#%02x%02x%02x", &r, &g, &b);
    mText.setFillColor(sf::Color(r, g, b));
}
