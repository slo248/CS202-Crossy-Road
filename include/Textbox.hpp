#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <iostream>
#include <sstream>

#include "Component.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace GUI;

class Textbox : public Component {
   public:
    typedef std::shared_ptr<Textbox> Ptr;

   public:
    Textbox(
        const std::string& text, const FontHolder& fonts,
        const TextureHolder& textures, int characterSize = 16
    );

    std::string getText() const;

    void typedOn(sf::Event input);
    virtual void handleEvent(const sf::Event& event);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void inputLogic(int charTyped);
    void deleteLastChar();
    void updateTextPosition();

   private:
    const sf::Texture& mBackgroundTexture;
    sf::Text mText;
    std::ostringstream text;
    sf::Sprite mBackground;
    sf::Vector2f size;
    int limit = 0;
    bool hasLimit = false;
};

#endif
