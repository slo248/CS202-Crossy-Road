#include "RankingState.hpp"

RankingState::RankingState(StateStack& stack, Context context)
    : mBackground(context.textures->get(Textures::BackgroundRanking)),
      State(stack, context) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(1254, 6)
    );
    buttonBack->setCallback(std::bind(&RankingState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);
}

void RankingState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mGUIContainer);
}
bool RankingState::update(sf::Time dt) { return 1; }
bool RankingState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return 0;
}
