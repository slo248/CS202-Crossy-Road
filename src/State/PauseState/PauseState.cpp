#include "PauseState.hpp"

#include "GameState.hpp"

#define ORIGIN_X 300.f
#define ORIGIN_Y 340.f

PauseState::PauseState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundPause)),
      State(stack, context) {
    auto buttonSaveGame = std::make_shared<Button>(
        context, Textures::ButtonSaveGame,
        sf::Vector2f(ORIGIN_X, ORIGIN_Y - 96.f), true
    );

    buttonSaveGame->setCallback([this]() {
        if (mContext->gameState) {
            mContext->gameState->save();
        }
    });
    mGUIContainer.pack(buttonSaveGame);

    auto buttonHome = std::make_shared<Button>(
        context, Textures::ButtonHome, sf::Vector2f(ORIGIN_X, ORIGIN_Y)
    );
    buttonHome->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Menu);
    });
    mGUIContainer.pack(buttonHome);

    auto buttonResumePause = std::make_shared<Button>(
        context, Textures::ButtonResumePause,
        sf::Vector2f(ORIGIN_X + 87, ORIGIN_Y)
    );
    buttonResumePause->setCallback([this]() { requestStackPop(); });
    mGUIContainer.pack(buttonResumePause);

    auto buttonPlayAgainPause = std::make_shared<Button>(
        context, Textures::ButtonPlayAgainPause,
        sf::Vector2f(ORIGIN_X + 174, ORIGIN_Y)
    );
    buttonPlayAgainPause->setCallback([this]() {
        mContext->isLoadedFromFile = false;
        requestStackClear();
        requestStackPush(States::Game);
    });
    mGUIContainer.pack(buttonPlayAgainPause);

    auto buttonSetting = std::make_shared<Button>(
        context, Textures::ButtonSetting, sf::Vector2f(ORIGIN_X + 262, ORIGIN_Y)
    );
    buttonSetting->setCallback([this]() {
        mContext->mode = Config::SettingState::NonSkin;
        mContext->musics->setPaused();
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
