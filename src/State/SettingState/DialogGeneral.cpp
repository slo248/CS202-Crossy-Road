#include "DialogGeneral.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

#define ORIGIN_Y 155.f
#define ORIGIN_MUSIC_Y (ORIGIN_Y + 153.f)
#define VOLUME_BAR_ALIGN 10.f

DialogGeneral::DialogGeneral(
    const sf::Texture& texture, State::Context& context
)
    : Dialog(texture, context),
      mLabelKeys(context.textures->get(Textures::LabelKeys)),
      mLabelMusic(context.textures->get(Textures::LabelMusic)),
      mLabelSfx(context.textures->get(Textures::LabelSfx)) {
    mSprite.setPosition(13.f, 112.f);

    // Keys area
    mLabelKeys.setPosition(174.f, ORIGIN_Y);
    addButtonLabel(
        Player::MoveLeft, ORIGIN_Y + 86.f, Textures::ButtonLeftArrow
    );
    addButtonLabel(
        Player::MoveRight, ORIGIN_Y + 153.f, Textures::ButtonRightArrow
    );
    addButtonLabel(Player::MoveUp, ORIGIN_Y + 221.f, Textures::ButtonUpArrow);
    addButtonLabel(
        Player::MoveDown, ORIGIN_Y + 303.f, Textures::ButtonDownArrow
    );
    updateLabels();

    // Music area
    mLabelMusic.setPosition(603.f, ORIGIN_Y);

    auto buttonMusic = std::make_shared<Button>(
        context, Textures::ButtonMusic, sf::Vector2f(493.f, ORIGIN_Y + 86.f),
        true
    );
    buttonMusic->setCallback([this, buttonMusic]() {
        handleVolume(buttonMusic, mContext->isMuteMusic);
    });
    mGUIContainer.pack(buttonMusic);

    mVolumeBarMusic = std::make_shared<VolumeBar>(
        context, 586.f, VOLUME_BAR_ALIGN + ORIGIN_Y + 86.f
    );
    mGUIContainer.pack(mVolumeBarMusic);

    mChosenMusic = std::make_shared<Button>(
        context, Textures::ChosenMusic, sf::Vector2f(586.f, ORIGIN_MUSIC_Y)
    );

    if (context.currentMusic) {
        mChosenMusic->setText(
            "Music " + std::to_string(context.currentMusic - 1), "#901212", 18,
            {630.f, ORIGIN_MUSIC_Y}
        );
    } else {
        mChosenMusic->setText("None", "#901212", 18, {630.f, ORIGIN_MUSIC_Y});
    }

    mChosenMusic->setCallback([this]() {
        if (mContext->mode) {
            isChoosingMusic = !isChoosingMusic;
        }
    });
    mGUIContainer.pack(mChosenMusic);

    addListMusic();

    // Sfx area
    mLabelSfx.setPosition(603.f, ORIGIN_Y + 221.f);

    auto buttonSound = std::make_shared<Button>(
        context, Textures::ButtonSound, sf::Vector2f(487.f, ORIGIN_Y + 221.f),
        true
    );
    buttonSound->setCallback([this, buttonSound]() {
        handleVolume(buttonSound, mContext->isMuteSfx);
    });
    mGUIContainer.pack(buttonSound);

    mVolumeBarSfx = std::make_shared<VolumeBar>(
        context, 586.f, VOLUME_BAR_ALIGN + ORIGIN_Y + 303.f, VolumeBar::Type::Sfx
    );
    mGUIContainer.pack(mVolumeBarSfx);
}

void DialogGeneral::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    states.transform *= getTransform();

    Dialog::draw(target, states);
    target.draw(mLabelKeys, states);
    target.draw(mLabelMusic, states);
    target.draw(mLabelSfx, states);
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

    if (isKeyBinding) updateLabels();

    mVolumeBarMusic->handleEvent(event);
    float volumeLevel = mVolumeBarMusic->getVolumeLevel();
    mContext->musics->setVolume(volumeLevel);

    mVolumeBarSfx->handleEvent(event);
    volumeLevel = mVolumeBarSfx->getVolumeLevel();
    mContext->soundEffects->setVolume(volumeLevel);

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
        *mContext, Textures::OptionMusic,
        sf::Vector2f(586.f, ORIGIN_MUSIC_Y + 28.f)
    );
    mListMusics[0]->setText(
        "None", "#901212", 18, {630.f, ORIGIN_MUSIC_Y + 28.f}
    );
    mListMusics[0]->setCallback([this]() {
        isChoosingMusic = false;
        mChosenMusic->setText(
            "None", "#901212", 18, {650.f, ORIGIN_MUSIC_Y + 12.f}
        );
        mContext->currentMusic = Musics::None;
    });

    for (int i = 1; i < Musics::MusicCount - 1; ++i) {
        mListMusics[i] = std::make_shared<Button>(
            *mContext, Textures::OptionMusic,
            sf::Vector2f(586.f, ORIGIN_MUSIC_Y + 28.f * (i + 1))
        );
        mListMusics[i]->setText(
            "Music" + std::to_string(i), "#901212", 18,
            {630.f, ORIGIN_MUSIC_Y + 28.f * (i + 1)}
        );
        mListMusics[i]->setCallback([this, i]() {
            isChoosingMusic = false;
            mChosenMusic->setText(
                "Music" + std::to_string(i), "#901212", 18,
                {650.f, ORIGIN_MUSIC_Y + 12.f}
            );
            mContext->currentMusic = static_cast<Musics::ID>(i + 1);
        });
    }
}

void DialogGeneral::handleVolume(Button::Ptr buttonVolume, bool& isMute) {
    if (isMute) {
        // code handle
        isMute = false;
        buttonVolume->deselect();
    } else {
        isMute = true;
    }
}
