#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics/Text.hpp>

#include "Component.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

namespace GUI {

class Label : public Component {
   public:
    typedef std::shared_ptr<Label> Ptr;

   public:
    Label(const std::string& text, const FontHolder& fonts);

    virtual bool isSelectable() const;
    void setText(const std::string& text);

    virtual void handleEvent(const sf::Event& event);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Text mText;
};

}  // namespace GUI

#endif  // BOOK_LABEL_HPP
