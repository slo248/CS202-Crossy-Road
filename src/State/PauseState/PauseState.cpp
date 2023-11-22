#include "PauseState.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : mBackground(context.textures->get(Textures::BackgroundPause)),
      State(stack, context) {
    auto buttonStar = std::make_shared<Button>(
        context, Textures::ButtonStar, sf::Vector2f(349, 366), true
    );
    mGUIContainer.pack(buttonStar);

    auto buttonHome = std::make_shared<Button>(
        context, Textures::ButtonHome, sf::Vector2f(349, 510)
    );
    mGUIContainer.pack(buttonHome);

    auto buttonResumePause = std::make_shared<Button>(
        context, Textures::ButtonResumePause, sf::Vector2f(480, 510)
    );
    mGUIContainer.pack(buttonResumePause);

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(742, 510)
    );
    buttonSetting->setCallback([this]() { requestStackPush(States::Setting); });
    mGUIContainer.pack(buttonSetting);

    auto buttonPlayAgainPause = std::make_shared<Button>(
        context, Textures::ButtonPlayAgainPause, sf::Vector2f(611, 510)
    );
    mGUIContainer.pack(buttonPlayAgainPause);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool PauseState::update(sf::Time dt) { return 1; }
bool PauseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return 0;
}
