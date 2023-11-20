#include "Button.hpp"

#include <SFML/Window/Event.hpp>

#include "Utility.hpp"

Button::Button(
    State::Context context, Textures::ID button, sf::Vector2f position,
    bool is2Mode
)
    : mCallback(),
      mSprite(context.textures->get(button)),
      mIsToggle(false),
      mIsOn(false),
      mIs2Mode(is2Mode),
      context(context) {
    originalPosition = position;
    mSprite.setPosition(originalPosition);
    if (mIs2Mode) {
        changeTexture(Normal);
    }
}

void Button::setCallback(Callback callback) { mCallback = std::move(callback); }

void Button::setToggle(bool flag) { mIsToggle = flag; }

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2f buttonPosition = mSprite.getPosition();
    sf::FloatRect buttonBounds = mSprite.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f convertedMousePosition =
        window.mapPixelToCoords(mousePosition);

    buttonBounds.left = buttonPosition.x;
    buttonBounds.top = buttonPosition.y;

    return buttonBounds.contains(convertedMousePosition);
}

bool Button::isSelectable() const { return true; }

void Button::select() {
    Component::select();
    
    if (mIs2Mode) {
        changeTexture(Selected);
    } else {
        if (mCallback) {
            mCallback();
        }
    }
}

void Button::deselect() {
    Component::deselect();

    changeTexture(Normal);
}

void Button::handleEvent(const sf::Event& event) {
    if (isMouseOver(*context.window)) {
        if (!mIsOn) {
            changeSize(Size::Small);
            mIsOn = true;
        }
    } else {
        if (mIsOn) {
            changeSize(Size::Medium);
            mIsOn = false;
        }
    }

    if (isMouseOver(*context.window) &&
        event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        select();
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

void Button::changeSize(Size buttonSize) {
    float scaleFactor = 1.0f;

    switch (buttonSize) {
        case Size::Small: {
            scaleFactor -= 0.2f;
            sf::FloatRect bounds = mSprite.getLocalBounds();
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.move(0.1f * bounds.width, 0.1f * bounds.height);
            break;
        }
        case Size::Medium: {
            scaleFactor = 1.0f;
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.setPosition(originalPosition);
            break;
        }
        case Size::Large: {
            scaleFactor += 0.2f;
            sf::FloatRect bounds = mSprite.getLocalBounds();
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.move(-0.1f * bounds.width, -0.1f * bounds.height);
            break;
        }
    }

    mSprite.setScale(scaleFactor, scaleFactor);
}

void Button::changeTexture(Mode buttonMode) {
    sf::Vector2u textureSize = mSprite.getTexture()->getSize();
    sf::IntRect textureRect(
        (textureSize.x / 2) * buttonMode, 0, textureSize.x / 2, textureSize.y
    );
    mSprite.setTextureRect(textureRect);
}
