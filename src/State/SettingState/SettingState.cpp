#include "SettingState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

SettingState::SettingState(StateStack& stack, Context& context)
    : State(stack, context),
      mWindow(context.window),
      mMode(static_cast<Config::SettingState::Mode>(context.mode)) {
    mChangeableSkin = true;
    mBackgroundSprite.setTexture(
        context.textures->get(Textures::BackgroundSetting)
    );

    mDialogGeneral = std::make_shared<DialogGeneral>(
        context.textures->get(Textures::DialogCommon), context
    );
    mButtonGeneral = std::make_shared<Button>(
        context, Textures::ButtonGeneral, sf::Vector2f(13, 79), true
    );
    mButtonGeneral->setCallback([this]() { this->mChangeableSkin = true; });
    mGUIContainer.pack(mButtonGeneral);

    if (mMode == Config::SettingState::Skin) {
        mDialogSkin = std::make_shared<DialogSkin>(
            context.textures->get(Textures::DialogCommon), context
        );
    }

    mButtonSkin = std::make_shared<Button>(
        context, Textures::ButtonSkin, sf::Vector2f(448, 79), true
    );

    if (mMode == Config::SettingState::Skin) {
        mButtonSkin->setCallback([this]() { this->mChangeableSkin = false; });
    }

    mGUIContainer.pack(mButtonSkin);

    auto backButton = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    backButton->setCallback([this]() { requestStackPop(); });
    mGUIContainer.pack(backButton);
}

void SettingState::draw() {
    if (mChangeableSkin) {
        mWindow->clear();
        mWindow->draw(mBackgroundSprite);
        mWindow->draw(mGUIContainer);
        mWindow->draw(*mDialogGeneral);
    } else if (!mChangeableSkin && mMode) {
        mWindow->clear();
        mWindow->draw(mBackgroundSprite);
        mWindow->draw(mGUIContainer);
        mWindow->draw(*mDialogSkin);
    }
}

bool SettingState::update(sf::Time dt) {
    if (mMode == Config::SettingState::Skin) {
        mDialogSkin->update(dt);
    }

    return false;
}

bool SettingState::handleEvent(const sf::Event& event) {
    if (mChangeableSkin) {
        mButtonGeneral->select();
        mButtonGeneral->isSelectable(false);
        mButtonSkin->deselect();
        mDialogGeneral->handleEvent(event);
    } else if (!mChangeableSkin && mMode == Config::SettingState::Skin) {
        mButtonGeneral->isSelectable(true);
        mButtonGeneral->deselect();
        mButtonSkin->select();
        mDialogSkin->handleEvent(event);
    }

    mGUIContainer.handleEvent(event);
    return false;
}
