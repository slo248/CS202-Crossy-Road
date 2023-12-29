#include "ChooseModeState.hpp"

#include <fstream>

#include "Config.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

ChooseModeState::ChooseModeState(StateStack& stack, Context& context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMenu)),
      mMode(static_cast<Config::ChooseModeState::Mode>(context.mode)) {
    auto buttonLevelMenu = std::make_shared<Button>(
        context, Textures::ButtonLevelMenu, sf::Vector2f(584, 320)
    );
    buttonLevelMenu->setCallback([this]() { requestStackPush(States::Level); });
    mGUIContainer.pack(buttonLevelMenu);

    auto buttonSurvival = std::make_shared<Button>(
        context, Textures::ButtonSurvival, sf::Vector2f(584, 373)
    );
    buttonSurvival->setCallback([this]() {
        mContext->gameLevel = Config::Game::Level::Survival;

        if (mMode == Config::ChooseModeState::Continue) {
            std::ifstream in(
                savedGamePath(Config::Game::Level::Survival), std::ios::in
            );

            mContext->isLoadedFromFile = false;

            if (in.good()) {
                in >> mContext->isLoadedFromFile;
            }
            in.close();

            requestStackClear();
            requestStackPush(States::Game);
        } else {
            mContext->isLoadedFromFile = false;
            requestStackClear();
            requestStackPush(States::Game);
        }
    });
    mGUIContainer.pack(buttonSurvival);

    auto buttonBackMenu = std::make_shared<Button>(
        context, Textures::ButtonBackMenu, sf::Vector2f(584, 426)
    );
    buttonBackMenu->setCallback(
        std::bind(&ChooseModeState::requestStackPop, this)
    );
    mGUIContainer.pack(buttonBackMenu);

    // Continue:
    // std::ifstream in(saveGamePath(choice), std::ios::in);
    // context.isLoadFromFile = true;
    // if (!in.good()) {
    //     context.isLoadFromFile = false;
    //     requestStackPush(States::GameState);
    // }
    //
    // in >> context.isLoadFromFile;
    // requestStackPush(States::GameState);
    // in.close();
}

void ChooseModeState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}
bool ChooseModeState::update(sf::Time dt) { return false; }

bool ChooseModeState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
