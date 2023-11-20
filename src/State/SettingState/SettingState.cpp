// #include "SettingState.hpp"

// #include "ResourceHolder.hpp"
// #include "Utility.hpp"

// SettingState::SettingState(StateStack& stack, Context context)
//     : State(stack, context) {
//     mBackgroundSprite.setTexture(
//         context.textures->get(Textures::SettingBackground)
//     );

//     addButton(Player::MoveLeft, 310.f, context.textures.get(Textures::MoveLeftButton), context);
//     addButton(Player::MoveRight, 411.f, context.textures.get(Textures::MoveRightButton), context);
//     addButton(Player::MoveUp, 512.f, context.textures.get(Textures::MoveUpButton), context);
//     addButton(Player::MoveDown, 635.f, context.te   xtures.get(Textures::MoveDownButton), context);

//     updateLabels();

//     auto backButton =
//         std::make_shared<Button>(*context.fonts, *context.textures);
//     backButton->setPosition(80.f, 375.f);
//     backButton->setCallback(std::bind(&SettingState::requestStackPop, this));

//     mGUIContainer.pack(backButton);
// }

// void SettingState::draw() {
//     sf::RenderWindow& window = *getContext().window;

//     window.draw(mBackgroundSprite);
//     window.draw(mGUIContainer);
// }

// bool SettingState::update(sf::Time) { return true; }

// bool SettingState::handleEvent(const sf::Event& event) {
//     bool isKeyBinding = false;

//     // Iterate through all key binding buttons to see if they are being pressed,
//     // waiting for the user to enter a key
//     for (std::size_t action = 0; action < Player::ActionCount; ++action) {
//         if (mBindingButtons[action]->isActive()) {
//             isKeyBinding = true;
//             if (event.type == sf::Event::KeyReleased) {
//                 getContext().player->assignKey(
//                     static_cast<Player::Action>(action), event.key.code
//                 );
//                 mBindingButtons[action]->deactivate();
//             }
//             break;
//         }
//     }

//     // If pressed button changed key bindings, update labels; otherwise consider
//     // other buttons in container
//     if (isKeyBinding)
//         updateLabels();
//     else
//         mGUIContainer.handleEvent(event);

//     return false;
// }

// void SettingState::updateLabels() {
//     Player& player = *getContext().player;

//     for (std::size_t i = 0; i < Player::ActionCount; ++i) {
//         sf::Keyboard::Key key =
//             player.getAssignedKey(static_cast<Player::Action>(i));
//         mBindingLabels[i]->setText(toString(key));
//     }
// }

// void SettingState::addAButtonLabel(
//     Player::Action action, float y, const sf::Texture& mNormal, Context context
// ) {
//     mBindingButtons[action] = std::make_shared<Button>(mNormal);
//     mBindingButtons[action]->setPosition(115.f, y);
//     mBindingButtons[action]->setToggle(true);

//     mBindingLabels[action] = std::make_shared<Label>("", *context.fonts);
//     mBindingLabels[action]->setPosition(334.f, y + 5.f);

//     mGUIContainer.pack(mBindingButtons[action]);
//     mGUIContainer.pack(mBindingLabels[action]);
// }

// void SettingState::addALabel
