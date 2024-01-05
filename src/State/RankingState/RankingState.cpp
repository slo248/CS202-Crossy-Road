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
        int score = (*mContext->highScores)[i].score;

        if (score > 0) {
            auto labelScore = std::make_shared<Label>(
                std::to_string(score), Fonts::Main, context, 22
            );

            labelScore->setPosition(500, 182 + 78 * i);
            labelScore->setColor("#901212");
            mGUIContainer.pack(labelScore);

            auto labelDate = std::make_shared<Label>(
                (*mContext->highScores)[i].date, Fonts::Main, context, 22
            );
            labelDate->setPosition(570, 182 + 78 * i);
            labelDate->setColor("#901212");
            mGUIContainer.pack(labelDate);
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
