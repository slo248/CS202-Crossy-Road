#include "DialogSuccess.hpp"

DialogSuccess::DialogSuccess(
    const sf::Texture& texture, State::Context& context
)
    : Dialog(texture, context) {
    mSprite.setPosition(136.f, 200.f);
    mIsActive = false;

    mButtonOK = std::make_shared<Button>(
        context, Textures::ButtonOK, sf::Vector2f(395, 433)
    );

    mButtonOK->setCallback([this]() { mIsActive = false; });
    mGUIContainer.pack(mButtonOK);
}

void DialogSuccess::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    if (!mIsActive) return;

    states.transform *= getTransform();
    Dialog::draw(target, states);
    target.draw(mGUIContainer, states);
}

void DialogSuccess::handleEvent(const sf::Event& event) {
    if (!mIsActive) return;

    mGUIContainer.handleEvent(event);
}
