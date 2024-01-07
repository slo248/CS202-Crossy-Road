#include "ChooseModeState.hpp"

#include <fstream>

#include "Config.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#define ORIGIN_X 584.f
#define ORIGIN_Y 320.f

ChooseModeState::ChooseModeState(StateStack& stack, Context& context)
    : State(stack, context),
      mBackgroundSprite(context.textures->get(Textures::BackgroundMenu)),
      mMode(static_cast<Config::ChooseModeState::Mode>(context.mode)) {
    auto buttonLevelMenu = std::make_shared<Button>(
        context, Textures::ButtonLevelMenu, sf::Vector2f(ORIGIN_X, ORIGIN_Y)
    );
    buttonLevelMenu->setCallback([this]() { requestStackPush(States::Level); });
    mGUIContainer.pack(buttonLevelMenu);

    auto buttonSurvival = std::make_shared<Button>(
        context, Textures::ButtonSurvival, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 53.f)
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
        context, Textures::ButtonBackMenu, sf::Vector2f(ORIGIN_X, ORIGIN_Y + 106.f)
    );
    buttonBackMenu->setCallback(
        std::bind(&ChooseModeState::requestStackPop, this)
    );
    mGUIContainer.pack(buttonBackMenu);
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
