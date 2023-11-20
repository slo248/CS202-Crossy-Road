#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Component.hpp"
#include "ResourceHolder.hpp"
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
        State::Context context, Textures::ID button, sf::Vector2f position = sf::Vector2f(0.f, 0.f),
        bool is2Mode = false
    );
    void setCallback(Callback callback);
    void setToggle(bool flag);

    virtual bool isMouseOver(const sf::RenderWindow& window) const;
    virtual bool isSelectable() const;
    virtual void select();
    virtual void deselect();

    virtual void handleEvent(const sf::Event& event);

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void changeSize(Size buttonSize);
    void changeTexture(Mode buttonMode);

   private:
    State::Context context;
    Callback mCallback;
    sf::Sprite mSprite;
    bool mIsToggle;
    bool mIsOn;
    bool mIs2Mode;
    sf::Vector2f originalPosition;
};

#endif
