#include "DialogGeneral.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

DialogGeneral::DialogGeneral(
    const sf::Texture& texture, State::Context& context
)
    : Dialog(texture, context),
      mLabelTextKeys(context.textures->get(Textures::LabelTextKeys)),
      mLabelTextSounds(context.textures->get(Textures::LabelTextSounds)),
      mVolumeBar(context) {
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
    buttonMusic->setCallback([this]() {});
    mGUIContainer.pack(buttonMusic);

    mChosenMusic = std::make_shared<Button>(
        context, Textures::ChosenMusic, sf::Vector2f(586.f, 320.f)
    );

    if (context.currentMusic) {
        mChosenMusic->setText(
            "Music " + std::to_string(context.currentMusic - 1), "#901212", 18,
            {630.f, 320.f}
        );
    } else {
        mChosenMusic->setText("None", "#901212", 18, {630.f, 320.f});
    }

    mChosenMusic->setCallback([this]() {
        if (mContext->mode) isChoosingMusic = !isChoosingMusic;
    });
    mGUIContainer.pack(mChosenMusic);

    float y = 241.f;
    addButtonLabel(Player::MoveLeft, y, Textures::ButtonLeftArrow);
    addButtonLabel(Player::MoveRight, y + 67.f, Textures::ButtonRightArrow);
    addButtonLabel(Player::MoveUp, y + 135.f, Textures::ButtonUpArrow);
    addButtonLabel(Player::MoveDown, y + 217.f, Textures::ButtonDownArrow);
    
    addListMusic();
    updateLabels();
}

void DialogGeneral::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    states.transform *= getTransform();

    Dialog::draw(target, states);
    target.draw(mLabelTextKeys, states);
    target.draw(mLabelTextSounds, states);
    target.draw(mVolumeBar, states);
    target.draw(mGUIContainer, states);
    if (isChoosingMusic) {
        for (int i = 0; i < Musics::MusicCount - 1; ++i) {
            target.draw(*mListMusics[i], states);
        }
    }
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
                mContext->player->assignKey(
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

    mVolumeBar.handleEvent(*(mContext->window), event);
    float volumeLevel = mVolumeBar.getVolumeLevel();
    mContext->musics->setVolume(volumeLevel);

    if (isKeyBinding) updateLabels();

    if (isChoosingMusic) {
        for (int i = 0; i < Musics::MusicCount - 1; ++i) {
            mListMusics[i]->handleEvent(event);
        }
    }
    mGUIContainer.handleEvent(event);
}

void DialogGeneral::updateLabels() {
    Player& player = *(mContext->player);

    for (std::size_t i = 0; i < Player::Count - 1; ++i) {
        sf::Keyboard::Key key = player.getKey(static_cast<Player::Action>(i));
        mBindingLabels[i]->setText(toString(key));
    }
}

void DialogGeneral::addButtonLabel(
    Player::Action action, float y, Textures::ID idTextures
) {
    mBindingButtons[action] = std::make_shared<Button>(
        *mContext, idTextures, sf::Vector2f(144.f, y), true
    );

    mBindingLabels[action] =
        std::make_shared<Label>("", Fonts::Main, *mContext);
    mBindingLabels[action]->setPosition(290.f, y + 25.f);
    mBindingLabels[action]->setColor("#901212");
    mGUIContainer.pack(mBindingButtons[action]);
    mGUIContainer.pack(mBindingLabels[action]);
}

void DialogGeneral::addListMusic() {
    mListMusics[0] = std::make_shared<Button>(
        *mContext, Textures::OptionMusic, sf::Vector2f(586.f, 348.f)
    );
    mListMusics[0]->setText("None", "#901212", 18, {630.f, 348.f});
    mListMusics[0]->setCallback([this]() {
        isChoosingMusic = false;
        mChosenMusic->setText("None", "#901212", 18, {650.f, 332.f});
        mContext->currentMusic = Musics::None;
    });

    for (int i = 1; i < Musics::MusicCount - 1; ++i) {
        mListMusics[i] = std::make_shared<Button>(
            *mContext, Textures::OptionMusic,
            sf::Vector2f(586.f, 348.f + 28 * i)
        );
        mListMusics[i]->setText(
            "Music" + std::to_string(i), "#901212", 18, {630.f, 348.f + 28 * i}
        );
        mListMusics[i]->setCallback([this, i]() {
            isChoosingMusic = false;
            mChosenMusic->setText(
                "Music" + std::to_string(i), "#901212", 18, {650.f, 332.f}
            );
            mContext->currentMusic = static_cast<Musics::ID>(i + 1);
        });
    }
}
