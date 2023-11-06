#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics/Text.hpp>

#include "Component.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

namespace GUI {

class Textbox : public Component {
   public:
    typedef std::shared_ptr<Textbox> Ptr;

   public:
    Textbox(
        const std::string& text, const FontHolder& fonts,
        const TextureHolder& textures
    );

    virtual bool isSelectable() const;
    void setText(const std::string& text);
    std::string getText() const;

    virtual void handleEvent(const sf::Event& event);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    const sf::Texture& mBackgroundTexture;
    sf::Text mText;
    sf::Sprite mBackground;
};

}  // namespace GUI

#endif  // BOOK_LABEL_HPP
