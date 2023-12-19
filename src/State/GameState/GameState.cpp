#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context& context)
    : State(stack, context),
      mPlayer(*context.player),
      mHighScores(context.highScores),
      mWorld(*context.textures, *context.fonts, *context.window, context) {
    context.gameState = this;
}

void GameState::draw() { mWorld.draw(); }

bool GameState::update(sf::Time dt) {
    // if player is dead but get new high score, then set status to HighScore
    if (mWorld.hasAlivePlayer()) {
        mWorld.update(dt);
        if (mWorld.hasPlayerReachedEnd()) {
            mPlayer.setStatus(Player::Success);
            requestStackPush(States::Win);
        }
    } else {
        Config::GameLevel::Type gameMode = mWorld.getGameType();
        int score = mWorld.getScore();

        if (gameMode == Config::GameLevel::Endless) {
            if (score > (*mHighScores)[0]) {
                (*mHighScores)[0] = score;
                mPlayer.setStatus(Player::HighScore);
                mContext->mode = 1;
                requestStackPush(States::Lose);

            } else {
                for (int i = 1; i < mHighScores->size(); ++i) {
                    if (score > (*mHighScores)[i]) {
                        (*mHighScores)[i] = score;
                    }
                }
                mPlayer.setStatus(Player::Failure);
                mContext->mode = 1;
                requestStackPush(States::Lose);
            }
        } else {
            mContext->mode = 0;
            requestStackPush(States::Lose);
        }
    }

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return true;
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

    return true;
}

void GameState::save() { mWorld.save(); }

Config::GameLevel::Type GameState::getGameType() const {
    return mWorld.getGameType();
}
