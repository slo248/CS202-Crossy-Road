#include "LevelState.hpp"

#include <fstream>

#include "ResourceHolder.hpp"
#include "Utility.hpp"

#define BAR_LEVEL_X 36.f
#define BAR_LEVEL_Y 153.f
#define TEXT_LEVEL_X (BAR_LEVEL_X + 240.f)
#define TEXT_LEVEL_Y (BAR_LEVEL_Y + 20.f)

LevelState::LevelState(StateStack& stack, Context& context)
    : State(stack, context),
      mBackground(context.textures->get(Textures::BackgroundLevel)),
      mMode(static_cast<Config::LevelState::Mode>(context.mode)) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack,
        sf::Vector2f(DEFAULT_BACK_BUTTON_X, DEFAULT_BACK_BUTTON_Y)
    );
    buttonBack->setCallback(std::bind(&LevelState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    addButtonLevel(5);
}

void LevelState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool LevelState::update(sf::Time dt) { return false; }

bool LevelState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}

void LevelState::addButtonLevel(int numLevel) {
    for (int i = 0; i < numLevel; ++i) {
        auto barLevel = std::make_shared<Button>(
            *mContext, Textures::BarLevel,
            sf::Vector2f(BAR_LEVEL_X, BAR_LEVEL_Y + 79 * i)
        );

        barLevel->setText(
            "Level " + std::to_string(i + 1), "#F2DAB5", 21,
            sf::Vector2f(TEXT_LEVEL_X, TEXT_LEVEL_Y + 79 * i)
        );

        barLevel->setCallback([this, i]() {
            mContext->gameLevel = static_cast<Config::Game::Level>(i);

            if (mMode == Config::LevelState::Continue) {
                std::ifstream in(
                    savedGamePath(static_cast<Config::Game::Level>(i)),
                    std::ios::in
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
        mGUIContainer.pack(barLevel);
    }
}
