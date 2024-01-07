#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "Component.hpp"
#include "Container.hpp"
#include "State.hpp"

// potentially problematic?
using namespace GUI;

class Dialog : public Component {
   public:
    typedef std::shared_ptr<Dialog> Ptr;

   public:
    Dialog(const sf::Texture& texture, State::Context& context);
    virtual void update(sf::Time dt){};
    virtual void handleEvent(const sf::Event& event) = 0;

   protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   protected:
    State::Context* mContext;
    Container mGUIContainer;
    const sf::Texture& mTexture;
    sf::Sprite mSprite;
};

#endif
