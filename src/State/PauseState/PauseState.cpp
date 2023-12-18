#include "PauseState.hpp"

PauseState::PauseState(StateStack& stack, Context& context, int mode)
    : mBackground(context.textures->get(Textures::BackgroundPause)),
      State(stack, context, mode) {
    int x = 300;

    auto buttonStar = std::make_shared<Button>(
        context, Textures::ButtonStar, sf::Vector2f(x, 244), true
    );
    mGUIContainer.pack(buttonStar);

    auto buttonHome = std::make_shared<Button>(
        context, Textures::ButtonHome, sf::Vector2f(300, 340)
    );
    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });
    mGUIContainer.pack(buttonHome);

    auto buttonResumePause = std::make_shared<Button>(
        context, Textures::ButtonResumePause, sf::Vector2f(x + 87, 340)
    );
    mGUIContainer.pack(buttonResumePause);

    auto buttonPlayAgainPause = std::make_shared<Button>(
        context, Textures::ButtonPlayAgainPause, sf::Vector2f(x + 174, 340)
    );
    mGUIContainer.pack(buttonPlayAgainPause);

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(x + 262, 340)
    );
    buttonSetting->setCallback([this]() { requestStackPush(States::Setting); });
    mGUIContainer.pack(buttonSetting);

    // buttonSaveGame
    // if (context.gameState) context.gameState->save();
}

void PauseState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool PauseState::update(sf::Time dt) { return 1; }
bool PauseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return 0;
}
