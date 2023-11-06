#include "Textbox.hpp"

#include "Utility.hpp"

namespace GUI {

Textbox::Textbox(
    const std::string& text, const FontHolder& fonts,
    const TextureHolder& textures, int characterSize
)
    : mBackgroundTexture(textures.get(Textures::TextBackground)) {
    mBackground.setTexture(mBackgroundTexture);
    size = sf::Vector2f(
        mBackground.getLocalBounds().width, mBackground.getLocalBounds().height
    );
    limit = mBackground.getLocalBounds().width / characterSize;

    mText.setFont(fonts.get(Fonts::Main));
    mText.setCharacterSize(characterSize);
    mText.setFillColor(sf::Color::White);
    mText.setString(text);
    updateTextPosition();
}

bool Textbox::isSelectable() const { return true; }

void Textbox::handleEvent(const sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        this->select();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->deselect();
        mText.setString(text.str());
    }

    if (event.type == sf::Event::TextEntered) {
        this->typedOn(event);
    }
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mBackground, states);
    target.draw(mText, states);
}

void Textbox::typedOn(sf::Event input) {
    if (isSelected()) {
        int charTyped = input.text.unicode;

        if (charTyped < 128) {
            if (hasLimit) {
                if (text.str().length() <= limit) {
                    inputLogic(charTyped);
                } else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                    deleteLastChar();
                }
            } else {
                inputLogic(charTyped);
            }
        }
    }
}

void Textbox::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY &&
        charTyped != ESCAPE_KEY) {
        text << static_cast<char>(charTyped);
    } else if (charTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            deleteLastChar();
        }
    }

    mText.setString(text.str() + "_");
    updateTextPosition();
}

void Textbox::deleteLastChar() {
    std::string t = text.str();
    std::string newT = "";

    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }

    text.str("");
    text << newT;

    mText.setString(text.str() + "_");
    updateTextPosition();
}

void Textbox::updateTextPosition() {
    sf::FloatRect textBounds = mText.getLocalBounds();
    mText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    mText.setPosition(mBackground.getPosition() + size * 0.5f);
}

std::string Textbox::getText() const { return mText.getString(); }

}  // namespace GUI
