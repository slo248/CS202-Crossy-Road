#include "PauseState.hpp"

#include "GameState.hpp"

PauseState::PauseState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundPause)),
      State(stack, context) {
    int x = 300;

    auto buttonSaveGame = std::make_shared<Button>(
        context, Textures::ButtonSaveGame, sf::Vector2f(x, 244), true
    );

    buttonSaveGame->setCallback([this]() {
        if (mContext->gameState) {
            mContext->gameState->save();
        }
    });
    mGUIContainer.pack(buttonSaveGame);

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
    buttonResumePause->setCallback([this]() { requestStackPop(); });
    mGUIContainer.pack(buttonResumePause);

    auto buttonPlayAgainPause = std::make_shared<Button>(
        context, Textures::ButtonPlayAgainPause, sf::Vector2f(x + 174, 340)
    );
    buttonPlayAgainPause->setCallback([this]() {
        mContext->isLoadedFromFile = false;
        requestStackClear();
        requestStackPush(States::Game);
    });
    mGUIContainer.pack(buttonPlayAgainPause);

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(x + 262, 340)
    );
    buttonSetting->setCallback([this]() {
        mContext->mode = Config::SettingState::NonSkin;
        requestStackPush(States::Setting);
    });
    mGUIContainer.pack(buttonSetting);
}

void PauseState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool PauseState::update(sf::Time dt) { return false; }

bool PauseState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
