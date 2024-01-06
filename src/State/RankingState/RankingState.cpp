#include "RankingState.hpp"

#define SCORE_X 497.f
#define FIRST_LINE_Y 170.f
#define DATE_X (SCORE_X + 73.f)
#define SECOND_LINE_Y (FIRST_LINE_Y + 25.f)

RankingState::RankingState(StateStack& stack, Context& context)
    : mBackground(context.textures->get(Textures::BackgroundRanking)),
      State(stack, context) {
    auto buttonBack = std::make_shared<Button>(
        context, Textures::ButtonBack,
        sf::Vector2f(DEFAULT_BACK_BUTTON_X, DEFAULT_BACK_BUTTON_Y)
    );
    buttonBack->setCallback(std::bind(&RankingState::requestStackPop, this));
    mGUIContainer.pack(buttonBack);

    for (int i = 0; i < mContext->highScores->size(); ++i) {
        int score = (*mContext->highScores)[i].score;

        if (score > 0) {
            auto labelScore =
                std::make_shared<Label>("Score", Fonts::Main, context, 18);
            labelScore->addStyle(sf::Text::Underlined);
            labelScore->setPosition(SCORE_X, FIRST_LINE_Y + 78 * i);
            labelScore->setColor("#901212");
            mGUIContainer.pack(labelScore);

            auto labelDate =
                std::make_shared<Label>("Date", Fonts::Main, context, 18);
            labelDate->addStyle(sf::Text::Underlined);
            labelDate->setPosition(DATE_X, FIRST_LINE_Y + 78 * i);
            labelDate->setColor("#901212");
            mGUIContainer.pack(labelDate);

            auto playerScore = std::make_shared<Label>(
                std::to_string(score), Fonts::Main, context, 22
            );

            playerScore->setPosition(SCORE_X, SECOND_LINE_Y + 78 * i);
            playerScore->setColor("#901212");
            mGUIContainer.pack(playerScore);

            auto datePlayed = std::make_shared<Label>(
                (*mContext->highScores)[i].date, Fonts::Main, context, 22
            );
            datePlayed->setPosition(DATE_X, SECOND_LINE_Y + 78 * i);
            datePlayed->setColor("#901212");
            mGUIContainer.pack(datePlayed);
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
