#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "Component.hpp"

using namespace GUI;

class Dialog : public Component {
   public:
    typedef std::shared_ptr<Dialog> Ptr;

   public:
    Dialog(
        const sf::Texture& texture
    );
    virtual bool isSelectable() const { return false; }
    virtual void handleEvent(const sf::Event& event){};

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   protected:
    sf::Text mText;
    const sf::Texture& mTexture;
    sf::Sprite mSprite;
};

#endif
