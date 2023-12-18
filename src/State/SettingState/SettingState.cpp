#include "SettingState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

SettingState::SettingState(StateStack& stack, Context& context, int mode)
    : State(stack, context, mode), mWindow(context.window) {
    mIsGeneral = true;
    mBackgroundSprite.setTexture(
        context.textures->get(Textures::BackgroundSetting)
    );

    mDialogGeneral = std::make_shared<DialogGeneral>(
        context.textures->get(Textures::DialogCommon), context
    );
    mButtonGeneral = std::make_shared<Button>(
        context, Textures::ButtonGeneral, sf::Vector2f(13, 79), true
    );
    mButtonGeneral->setCallback([this]() { this->mIsGeneral = true; });
    mGUIContainer.pack(mButtonGeneral);

    if (mMode) {
        mDialogSkin = std::make_shared<DialogSkin>(
            context.textures->get(Textures::DialogCommon), context
        );
    }

    mButtonSkin = std::make_shared<Button>(
        context, Textures::ButtonSkin, sf::Vector2f(448, 79), true
    );

    if (mMode) {
        mButtonSkin->setCallback([this]() { this->mIsGeneral = false; });
    }

    mGUIContainer.pack(mButtonSkin);

    auto backButton = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    backButton->setCallback(std::bind(&SettingState::requestStackPop, this));
    mGUIContainer.pack(backButton);
}

void SettingState::draw() {
    if (mIsGeneral) {
        mWindow->clear();
        mWindow->draw(mBackgroundSprite);
        mWindow->draw(mGUIContainer);
        mWindow->draw(*mDialogGeneral);
    } else if (!mIsGeneral && mMode) {
        mWindow->clear();
        mWindow->draw(mBackgroundSprite);
        mWindow->draw(mGUIContainer);
        mWindow->draw(*mDialogSkin);
    }
}

bool SettingState::update(sf::Time dt) {
    if (mMode) {
        mDialogSkin->update(dt);
    }

    return true;
}

bool SettingState::handleEvent(const sf::Event& event) {
    if (mIsGeneral) {
        mButtonGeneral->select();
        mButtonGeneral->isSelectable(false);
        mButtonSkin->deselect();
        mDialogGeneral->handleEvent(event);
    } else if (!mIsGeneral && mMode) {
        mButtonGeneral->isSelectable(true);
        mButtonGeneral->deselect();
        mButtonSkin->select();
        mDialogSkin->handleEvent(event);
    }

    mGUIContainer.handleEvent(event);
    return false;
}
