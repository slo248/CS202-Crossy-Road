#include "LevelState.hpp"

#include "ResourceHolder.hpp"

LevelState::LevelState(StateStack& stack, Context context)
    : State(stack, context),
      mBackground(context.textures->get(Textures::BackgroundLevel)) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    buttonBack->setCallback(std::bind(&LevelState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    int numLevel = 5;
    for (int i = 0; i < numLevel; ++i) {
        auto barLevel = std::make_shared<Button>(
            context, Textures::BarLevel, sf::Vector2f(36, 150 + 79 * i)
        );
        mGUIContainer.pack(barLevel);
    }
}

void LevelState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool LevelState::update(sf::Time dt) { return true; }

bool LevelState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
