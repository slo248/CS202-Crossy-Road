#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "Component.hpp"
#include "State.hpp"

using namespace GUI;

class Button : public Component {
   public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Callback;

    enum Mode { Normal, Selected, ModeCount };
    enum Size { Small, Medium, Large, SizeCount };

   public:
    Button(
        State::Context& context, Textures::ID button,
        sf::Vector2f position = sf::Vector2f(0.f, 0.f), bool is2Mode = false
    );
    void setCallback(Callback callback);
    void setText(
        const std::string& text, const std::string& hexCode, int characterSize,
        sf::Vector2f position, Fonts::ID font = Fonts::Main
    );

    virtual void select() override;
    virtual void deselect() override;

    virtual void handleEvent(const sf::Event& event) override;

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void callBack();
    void changeSize(Size buttonSize);
    void changeTexture(Mode buttonMode);
    bool isMouseOver(const sf::RenderWindow& window) const;

   private:
    Callback mCallback;
    sf::Sprite mSprite;
    sf::Text mText;
    sf::Vector2f originalPosition;
    sf::Vector2f textOriginalPosition;
    sf::FloatRect originalSize;
    State::Context* mContext;
    bool mIsToggle;
    bool mIsOn;
    bool mIs2Mode;
};

#endif
