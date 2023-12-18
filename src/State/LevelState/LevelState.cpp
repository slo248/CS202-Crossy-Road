#include "LevelState.hpp"

#include "ResourceHolder.hpp"

LevelState::LevelState(StateStack& stack, Context& context, int mode)
    : State(stack, context, mode),
      mBackground(context.textures->get(Textures::BackgroundLevel)) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    buttonBack->setCallback(std::bind(&LevelState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    addButtonLevel(context, 5);
}

void LevelState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool LevelState::update(sf::Time dt) { return true; }

bool LevelState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}

void LevelState::addButtonLevel(State::Context& context, const int& numLevel) {
    for (int i = 0; i < numLevel; ++i) {
        auto barLevel = std::make_shared<Button>(
            context, Textures::BarLevel, sf::Vector2f(36, 153 + 79 * i)
        );

        barLevel->setText(
            "Level " + std::to_string(i + 1), "#F2DAB5", 21,
            sf::Vector2f(276, 173 + 79 * i)
        );

        mGUIContainer.pack(barLevel);
    }
}
