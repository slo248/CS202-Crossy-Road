#include "DialogGeneral.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

DialogGeneral::DialogGeneral(const sf::Texture& texture, State::Context context)
    : Dialog(texture, context),
      mLabelTextKeys(context.textures->get(Textures::LabelTextKeys)),
      mLabelTextSounds(context.textures->get(Textures::LabelTextSounds)) {
    mSprite.setPosition(13.f, 112.f);
    mLabelTextKeys.setPosition(174.f, 155.f);
    mLabelTextSounds.setPosition(603.f, 155.f);

    auto buttonSound = std::make_shared<Button>(
        context, Textures::ButtonSound, sf::Vector2f(487.f, 238.f)
    );
    mGUIContainer.pack(buttonSound);

    auto buttonMusic = std::make_shared<Button>(
        context, Textures::ButtonMusic, sf::Vector2f(493.f, 315.f)
    );
    mGUIContainer.pack(buttonMusic);

    float y = 241.f;
    addButtonLabel(Player::MoveLeft, y, Textures::ButtonLeftArrow, mContext);
    addButtonLabel(
        Player::MoveRight, y + 67.f, Textures::ButtonRightArrow, mContext
    );
    addButtonLabel(
        Player::MoveUp, y + 135.f, Textures::ButtonUpArrow, mContext
    );
    addButtonLabel(
        Player::MoveDown, y + 217.f, Textures::ButtonDownArrow, mContext
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
        context, idTextures, sf::Vector2f(144.f, y), true
    );

    mBindingLabels[action] = std::make_shared<Label>("", Fonts::Main, context);
    mBindingLabels[action]->setPosition(290.f, y + 25.f);
    mBindingLabels[action]->setColor("#901212");
    mGUIContainer.pack(mBindingButtons[action]);
    mGUIContainer.pack(mBindingLabels[action]);
}
