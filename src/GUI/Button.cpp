#include "Button.hpp"

#include <SFML/Window/Event.hpp>

#include "Utility.hpp"

Button::Button(
    State::Context& context, Textures::ID button, sf::Vector2f position,
    bool is2Mode
)
    : mCallback(),
      mSprite(context.textures->get(button)),
      mText(),
      mIsToggle(false),
      mIsOn(false),
      mIs2Mode(is2Mode),
      mContext(context) {
    originalPosition = position;
    textOriginalPosition = sf::Vector2f(0, 0);
    mSprite.setPosition(originalPosition);
    if (mIs2Mode) {
        changeTexture(Normal);
    }
}

void Button::setCallback(Callback callback) { mCallback = std::move(callback); }

void Button::setToggle(bool flag) { mIsToggle = flag; }

void Button::setText(
    const std::string& text, const std::string& hexCode, int characterSize,
    sf::Vector2f position, Fonts::ID font
) {
    mText.setString(text);
    centerOrigin(mText);
    textOriginalPosition = position;

    mText.setFont(mContext.fonts->get(font));

    unsigned int r, g, b;
    sscanf(hexCode.c_str(), "#%02x%02x%02x", &r, &g, &b);
    mText.setFillColor(sf::Color(r, g, b));

    mText.setCharacterSize(characterSize);

    mText.setPosition(position);
}

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

void Button::select() {
    if (!mIsSelectable) return;
    Component::select();

    if (mIs2Mode) {
        changeTexture(Selected);
        callBack();
    } else {
        callBack();
    }
}

void Button::callBack() {
    if (mCallback) {
        mCallback();
    }
}

void Button::deselect() {
    Component::deselect();

    changeTexture(Normal);
}

void Button::handleEvent(const sf::Event& event) {
    if (isMouseOver(*mContext.window)) {
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

    if (isMouseOver(*mContext.window) &&
        event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        select();
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

void Button::changeSize(Size buttonSize) {
    float scaleFactor = 1.0f;

    switch (buttonSize) {
        case Size::Small: {
            scaleFactor -= 0.2f;
            sf::FloatRect bounds = mSprite.getLocalBounds();
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.move(0.1f * bounds.width, 0.1f * bounds.height);
            mText.setScale(scaleFactor, scaleFactor);
            mText.move(0.1f * bounds.width, 0.1f * bounds.height);
            break;
        }
        case Size::Medium: {
            scaleFactor = 1.0f;
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.setPosition(originalPosition);
            mText.setScale(scaleFactor, scaleFactor);
            mText.setPosition(textOriginalPosition);
            break;
        }
        case Size::Large: {
            scaleFactor += 0.2f;
            sf::FloatRect bounds = mSprite.getLocalBounds();
            mSprite.setScale(scaleFactor, scaleFactor);
            mSprite.move(-0.1f * bounds.width, -0.1f * bounds.height);
            mText.setScale(scaleFactor, scaleFactor);
            mText.move(-0.1f * bounds.width, -0.1f * bounds.height);
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
