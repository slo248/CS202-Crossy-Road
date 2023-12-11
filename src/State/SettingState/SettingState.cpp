#include "SettingState.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"

SettingState::SettingState(StateStack& stack, Context context, int mode)
    : State(stack, context, mode) {
    mBackgroundSprite.setTexture(
        context.textures->get(Textures::BackgroundSetting)
    );

    auto dialogGeneral = std::make_shared<DialogGeneral>(
        context.textures->get(Textures::DialogGeneral), context
    );
    mGUIContainer.pack(dialogGeneral);

    auto buttonGeneral = std::make_shared<Button>(
        context, Textures::ButtonGeneral, sf::Vector2f(13, 79)
    );
    mGUIContainer.pack(buttonGeneral);

    auto buttonSkin = std::make_shared<Button>(
        context, Textures::ButtonSkin, sf::Vector2f(448, 79)
    );
    mGUIContainer.pack(buttonSkin);

    auto backButton = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    backButton->setCallback(std::bind(&SettingState::requestStackPop, this));
    mGUIContainer.pack(backButton);
}

void SettingState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool SettingState::update(sf::Time) { return true; }

bool SettingState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
