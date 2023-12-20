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
    void setToggle(bool flag);
    void setText(
        const std::string& text, const std::string& hexCode, int characterSize,
        sf::Vector2f position, Fonts::ID font = Fonts::Main
    );

    virtual bool isMouseOver(const sf::RenderWindow& window) const override;
    virtual void select() override;
    void callBack();
    virtual void deselect() override;

    virtual void handleEvent(const sf::Event& event);

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void changeSize(Size buttonSize);
    void changeTexture(Mode buttonMode);

   private:
    Callback mCallback;
    sf::Sprite mSprite;
    sf::Text mText;
    bool mIsToggle;
    bool mIsOn;
    bool mIs2Mode;
    State::Context* mContext;
    sf::Vector2f originalPosition;
    sf::Vector2f textOriginalPosition;
    sf::FloatRect originalSize;
};

#endif
