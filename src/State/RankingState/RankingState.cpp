#include "RankingState.hpp"

RankingState::RankingState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundRanking)),
      State(stack, context) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack, sf::Vector2f(836, 4)
    );
    buttonBack->setCallback(std::bind(&RankingState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    for (int i = 0; i < mContext->highScores->size(); ++i) {
        int score = (*mContext->highScores)[i];

        if (score > 0) {
            auto labelRanking = std::make_shared<Label>(
                std::to_string(score), Fonts::Main, context
            );

            labelRanking->setPosition(590, 180 + 78 * i);
            labelRanking->setColor("#901212");
            mGUIContainer.pack(labelRanking);
        } else {
            break;
        }
    }
}

void RankingState::draw() {
    sf::RenderWindow& window = *(mContext->window);

    window.draw(mBackground);
    window.draw(mGUIContainer);
}

bool RankingState::update(sf::Time dt) { return false; }

bool RankingState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}
