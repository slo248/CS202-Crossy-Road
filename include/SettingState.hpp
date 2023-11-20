// #ifndef SETTING_STATE_HPP
// #define SETTING_STATE_HPP

// #include "Button.hpp"
// #include "Container.hpp"
// #include "Label.hpp"
// #include "Player.hpp"
// #include <SFML/Graphics.hpp>
// #include <array>

// #include "State.hpp"

// // Forward declaration
// class Player;
// //

// class SettingState : public State {
//    public:
//     SettingState(StateStack& stack, Context context);

//     virtual void draw();
//     virtual bool update(sf::Time dt);
//     virtual bool handleEvent(const sf::Event& event);

//    private:
//     void updateLabels();
//     void addAButtonLabel(
//         Player::Action action, float y, const sf::Texture& mNormal, Context context
//     );
//     void addButtons();
//     void addLabels();

//    private:
//     sf::Sprite mBackgroundSprite;
//     std::array<Button::Ptr, Player::ActionCount> mBindingButtons;
//     std::array<Label::Ptr, Player::ActionCount> mBindingLabels;
// };

// #endif  // BOOK_SettingSTATE_HPP
