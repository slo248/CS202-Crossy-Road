#include "Textbox.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Utility.hpp"

namespace GUI {

Textbox::Textbox(
    const std::string& text, const FontHolder& fonts,
    const TextureHolder& textures
)
    : mText(text, fonts.get(Fonts::Main), 16),
      mBackgroundTexture(textures.get(Textures::TextBackground)) {
    mBackground.setTexture(mBackgroundTexture);
    sf::FloatRect bounds = mBackground.getLocalBounds();
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

bool Textbox::isSelectable() const { return true; }

void Textbox::handleEvent(const sf::Event&) {
    
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
    target.draw(mBackground, states);
}

void Textbox::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

std::string Textbox::getText() const { return mText.getString(); }

}  // namespace GUI
