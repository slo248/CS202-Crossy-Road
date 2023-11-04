// #ifndef BUTTON_HPP
// #define BUTTON_HPP

// #include <SFML/Graphics/Sprite.hpp>
// #include <SFML/Graphics/Text.hpp>
// #include <functional>
// #include <memory>
// #include <string>
// #include <vector>


// namespace GUI {

// class Button : public Component {
//    public:
//     typedef std::shared_ptr<Button> Ptr;
//     typedef std::function<void()> Callback;

//    public:
//     Button(/*const FontHolder& fonts, const TextureHolder& textures*/);

//     void setCallback(Callback callback);
//     void setText(const std::string& text);
//     void setToggle(bool flag);

//     bool isSelectable() const override;
//     void select() override;
//     void deselect() override;

//     void activate() override;
//     void deactivate() override;

//     void handleEvent(const sf::Event& event) override;
//     sf::Texture mNormalTexture;
//     sf::Texture mSelectedTexture;
//     sf::Texture mPressedTexture;

//    private:
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//    private:
//     Callback mCallback;

//     // After having resource holder, this would change to const sf::Texture&
//     sf::Sprite mSprite;
//     sf::Text mText;
//     bool mIsToggle;
// };

// }  // namespace GUI

// #endif  // BOOK_BUTTON_HPP

