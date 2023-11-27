#include "DialogGeneral.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

DialogGeneral::DialogGeneral(const sf::Texture& texture, State::Context context)
    : Dialog(texture, context),
      mLabelTextKeys(context.textures->get(Textures::LabelTextKeys)),
      mLabelTextSounds(context.textures->get(Textures::LabelTextSounds)) {
    mSprite.setPosition(21.f, 146.f);
    mLabelTextKeys.setPosition(164.f, 180.f);
    mLabelTextSounds.setPosition(791.f, 180.f);

    auto saveButton = std::make_shared<Button>(
        context, Textures::ButtonSave, sf::Vector2f(484.f, 759.f)
    );
    mGUIContainer.pack(saveButton);  // do we really need a save button in this?

    auto buttonSound = std::make_shared<Button>(
        context, Textures::ButtonSound, sf::Vector2f(621.f, 315.f)
    );
    mGUIContainer.pack(buttonSound);

    auto buttonMusic = std::make_shared<Button>(
        context, Textures::ButtonMusic, sf::Vector2f(631.f, 420.f)
    );
    mGUIContainer.pack(buttonMusic);

    float y = 310.f;
    addButtonLabel(Player::MoveLeft, y, Textures::ButtonLeftArrow, mContext);
    addButtonLabel(
        Player::MoveRight, y + 101.f, Textures::ButtonRightArrow, mContext
    );
    addButtonLabel(
        Player::MoveUp, y + 202.f, Textures::ButtonUpArrow, mContext
    );
    addButtonLabel(
        Player::MoveDown, y + 325.f, Textures::ButtonDownArrow, mContext
    );

    updateLabels();
}

void DialogGeneral::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    states.transform *= getTransform();

    Dialog::draw(target, states);
    target.draw(mLabelTextKeys, states);
    target.draw(mLabelTextSounds, states);
    target.draw(mGUIContainer, states);
}

void DialogGeneral::handleEvent(const sf::Event& event) {
    bool isKeyBinding = false;

    for (std::size_t action = 0; action < Player::Count - 1; ++action) {
        if (mBindingButtons[action]->isSelected()) {
            for (std::size_t i = 0; i < Player::Count - 1; ++i) {
                if (i != action) mBindingButtons[i]->isSelectable(false);
            }

            isKeyBinding = true;

            if (event.type == sf::Event::KeyReleased) {
                mContext.player->assignKey(
                    static_cast<Player::Action>(action), event.key.code
                );

                mBindingButtons[action]->deselect();

                for (std::size_t i = 0; i < Player::Count - 1; ++i) {
                    mBindingButtons[i]->isSelectable(true);
                }
            }

            break;
        }
    }

    if (isKeyBinding) updateLabels();

    mGUIContainer.handleEvent(event);
}

void DialogGeneral::updateLabels() {
    Player& player = *mContext.player;

    for (std::size_t i = 0; i < Player::Count - 1; ++i) {
        sf::Keyboard::Key key = player.getKey(static_cast<Player::Action>(i));
        mBindingLabels[i]->setText(toString(key));
    }
}

void DialogGeneral::addButtonLabel(
    Player::Action action, float y, Textures::ID idTextures,
    State::Context context
) {
    mBindingButtons[action] = std::make_shared<Button>(
        context, idTextures, sf::Vector2f(115.f, y), true
    );

    mBindingLabels[action] = std::make_shared<Label>("", Fonts::Main, context);
    mBindingLabels[action]->setPosition(334.f, y + 25.f);

    mGUIContainer.pack(mBindingButtons[action]);
    mGUIContainer.pack(mBindingLabels[action]);
}                                                                  
