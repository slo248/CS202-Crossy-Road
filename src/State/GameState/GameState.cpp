#include "GameState.hpp"

#include "Config.hpp"

GameState::GameState(StateStack& stack, Context& context)
    : State(stack, context),
      mPlayer(*context.player),
      mHighScores(context.highScores),
      mWorld(*context.textures, *context.fonts, *context.window, context),
      mCountdown(nullptr) {
    context.gameState = this;

    mCountdown = std::make_unique<Animation>(
        context.textures->get(Textures::CountDown),
        sf::Vector2i(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), 3, -1, true
    );
    mCountdown->setPosition(DEFAULT_CELL_LENGTH * 7, DEFAULT_CELL_LENGTH * 5);
    mCountdown->setDuration(sf::seconds(3));
    mCountdown->setRepeat(false);

    if (context.isLoadedFromFile) {
        mCountdown->play();
    }
}

void GameState::draw() {
    mWorld.draw();

    if (mCountdown->isInProgress()) {
        mContext->window->draw(*mCountdown);
        return;
    }
}

bool GameState::update(sf::Time dt) {
    if (mCountdown->isInProgress()) {
        mCountdown->update(dt);
        return false;
    }

    // if player is dead but get new high score, then set status to HighScore
    if (mWorld.hasAlivePlayer()) {
        mWorld.update(dt);
        if (mWorld.hasPlayerReachedEnd()) {
            mContext->mode = Config::WinState::Win;
            requestStackPush(States::Win);
        }
    } else {
        if (mWorld.getGameType() == Config::GameLevel::Survival) {
            if (updateHighScore()) {
                mContext->mode = Config::WinState::HighScore;
                requestStackClear();
                requestStackPush(States::Win);
            } else {
                mContext->mode = Config::LoseState::Survival;
                requestStackClear();
                requestStackPush(States::Lose);
            }
        } else {
            mContext->mode = Config::LoseState::Lose;
            requestStackClear();
            requestStackPush(States::Lose);
        }
    }

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return false;
}

bool GameState::handleEvent(const sf::Event& event) {
    // Game input handling
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::Pause);
    }

    return false;
}

void GameState::save() { mWorld.save(); }

Config::GameLevel::Type GameState::getGameType() const {
    return mWorld.getGameType();
}

bool GameState::updateHighScore() {
    int score = mWorld.getScore();
    int tmp = score;
    bool flag = false;

    for (int i = 0; i < mContext->highScores->size(); ++i) {
        if (score > (*mContext->highScores)[i]) {
            tmp = (*mContext->highScores)[i];
            (*mContext->highScores)[i] = score;
            score = tmp;
            if (i == 0) {
                flag = true;
            }
        }
    }

    return flag;
}
