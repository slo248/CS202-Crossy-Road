#include "GameState.hpp"

#include "Config.hpp"
#include "Utility.hpp"

GameState::GameState(StateStack& stack, Context& context)
    : State(stack, context),
      mPlayer(*context.player),
      mHighScores(context.highScores),
      mWorld(context),
      mCountDown(nullptr) {
    context.gameState = this;

    if (context.isLoadedFromFile) {
        setupCountDown(context);
    }

    context.musics->play(context.currentMusic);
}

void GameState::draw() {
    mWorld.draw();

    if (mCountDown && mCountDown->isInProgress()) {
        mContext->window->draw(*mCountDown);
        return;
    }
}

bool GameState::update(sf::Time dt) {
    if (mCountDown && mCountDown->isInProgress()) {
        mCountDown->update(dt);
        return false;
    }

    // if player is dead but get new high score, then set status to HighScore
    if (mWorld.hasAlivePlayer()) {
        mWorld.update(dt);
        if (mWorld.hasPlayerReachedEnd()) {
            mContext->musics->stop();
            mContext->mode = Config::WinState::Win;
            requestStackPush(States::Win);
        }
    } else {
        mContext->musics->stop();
        if (mWorld.getGameType() == Config::Game::Level::Survival) {
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

Config::Game::Level GameState::getGameType() const {
    return mWorld.getGameType();
}

bool GameState::updateHighScore() {
    int score = mWorld.getScore();
    int tmp = score;
    bool flag = false;

    for (int i = 0; i < mContext->highScores->size(); ++i) {
        if (score > (*mContext->highScores)[i].score) {
            tmp = (*mContext->highScores)[i].score;
            (*mContext->highScores)[i].score = score;
            (*mContext->highScores)[i].date = getCurrentDateTime();
            score = tmp;
            if (i == 0) {
                flag = true;
            }
        }
    }

    return flag;
}

void GameState::setupCountDown(Context& context) {
    mCountDown = std::make_unique<Animation>(
        context.textures->get(Textures::CountDown),
        sf::Vector2i(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT), true
    );

    mCountDown->setPosition(
        DEFAULT_SCREEN_WIDTH / 2.f, DEFAULT_SCREEN_HEIGHT / 2.f
    );
    mCountDown->setDuration(DEFAULT_COUNTDOWN_DURATION);
    mCountDown->setRepeat(false);
    mCountDown->play();
}
