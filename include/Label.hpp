#ifndef LABEL_HPP
#define LABEL_HPP

#include "Component.hpp"

using namespace GUI;

class Label : public Component {
   public:
    typedef std::shared_ptr<Label> Ptr;

   public:
    Label(
        const std::string& text, const FontHolder& fonts,
        const TextureHolder& textures, int characterSize = 16
    );

    virtual bool isSelectable() const { return false; };
    virtual void handleEvent(const sf::Event& event){};

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Text mText;
    const sf::Texture& mTexture;
    sf::Sprite mSprite;
};

#endif
