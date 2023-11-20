#include "WinState.hpp"

#include "ResourceHolder.hpp"

WinState::WinState(StateStack& stack, Context context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mDialogVictory(context.textures->get(Textures::DialogVictory)) {
    mDialogVictory.setPosition(222.f, 147.f);

    auto buttonHome = std::make_shared<Button>(
        context, Textures::ButtonHome, sf::Vector2f(38.f, 841.f)
    );
    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(1024.f, 841.f)
    );
    buttonSetting->setCallback([this]() { requestStackPush(States::Setting); });

    auto buttonLevel = std::make_shared<Button>(
        context, Textures::ButtonLevel, sf::Vector2f(413.f, 531.f)
    );
    buttonLevel->setCallback([this]() { requestStackPush(States::Level); });

    auto buttonPlayAgain = std::make_shared<Button>(
        context, Textures::ButtonPlayAgain, sf::Vector2f(554.f, 531.f)
    );

    auto buttonResume = std::make_shared<Button>(
        context, Textures::ButtonResume, sf::Vector2f(695.f, 531.f)
    );
    buttonResume->setCallback([this]() {
        requestStackPop();
        requestStackPush(States::Game);
    });

    mGUIContainer.pack(buttonHome);
    mGUIContainer.pack(buttonSetting);
    mGUIContainer.pack(buttonLevel);
    mGUIContainer.pack(buttonPlayAgain);
    mGUIContainer.pack(buttonResume);
}

void WinState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackgroundSprite);
    window.draw(mDialogVictory);
    window.draw(mGUIContainer);
}

bool WinState::update(sf::Time dt) { return true; }

bool WinState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
