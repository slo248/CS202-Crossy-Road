#include "WinState.hpp"

#include "ResourceHolder.hpp"

WinState::WinState(StateStack& stack, Context context, int mode)
    : State(stack, context, mode),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMain)),
      mDialogVictory(context.textures->get(Textures::DialogVictory)) {
    mDialogVictory.setPosition(211.f, 98.f);

    auto buttonHome = std::make_shared<Button>(
        context, Textures::ButtonHome, sf::Vector2f(25.f, 560.f)
    );
    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(810.f, 560.f)
    );
    buttonSetting->setCallback([this]() { requestStackPush(States::Setting); });

    auto buttonLevel = std::make_shared<Button>(
        context, Textures::ButtonLevel, sf::Vector2f(339.f, 364.f)
    );
    buttonLevel->setCallback([this]() { requestStackPush(States::Level); });

    auto buttonPlayAgain = std::make_shared<Button>(
        context, Textures::ButtonPlayAgain, sf::Vector2f(433.f, 364.f)
    );

    auto buttonResume = std::make_shared<Button>(
        context, Textures::ButtonResume, sf::Vector2f(527.f, 364.f)
    );
    // buttonResume->setCallback([this]() {
    //     requestStackPop();
    //     requestStackPush(States::Game);
    // });

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
