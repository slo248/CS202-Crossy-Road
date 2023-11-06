#include "Dialog.hpp"

namespace GUI {

Dialog::Dialog(
    const sf::Font& font, const std::string& message,
    const sf::Vector2f& positionMessage
) {
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setString(message);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(positionMessage);
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) {
    states.transform *= getTransform();
    target.draw(backgroundBox, states);
    target.draw(messageText, states);
}

}  // namespace GUI
