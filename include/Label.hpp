#ifndef LABEL_HPP
#define LABEL_HPP

#include "Component.hpp"
#include "State.hpp"

using namespace GUI;

class Label : public Component {
   public:
    typedef std::shared_ptr<Label> Ptr;

   public:
    Label(
        const std::string& text, Fonts::ID font, State::Context& context,
        int characterSize = 33
    );

    void setText(const std::string& text);
    virtual void handleEvent(const sf::Event& event) override {};
    void setColor(const std::string& hexCode);
    void addStyle(sf::Text::Style style);

   private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Text mText;
};

#endif
