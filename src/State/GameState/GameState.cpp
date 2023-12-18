#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context& context)
    : State(stack, context),
      mPlayer(*context.player),
      mHighScores(context.highScores),
      mWorld(
          *context.textures, *context.fonts, *context.window,
          static_cast<Config::GameLevel::Type>(context.mode),
          context.isLoadedFromFile
      ) {
    context.gameState = this;
}

void GameState::draw() { mWorld.draw(); }

bool GameState::update(sf::Time dt) {
    mWorld.update(dt);

    // if player is dead but get new high score, then set status to HighScore
    if (!mWorld.hasAlivePlayer()) {
        Config::GameLevel::Type gameMode = mWorld.getGameType();
        int score = mWorld.getScore();

        if (gameMode == Config::GameLevel::Endless &&
            score > (*mHighScores)[0]) {
            (*mHighScores)[0] = score;
            mPlayer.setStatus(Player::HighScore);
        } else {
            for (int i = 1; i < mHighScores->size(); ++i) {
                if (score > (*mHighScores)[i]) {
                    (*mHighScores)[i] = score;
                }
            }
            mPlayer.setStatus(Player::Failure);
        }
        // requestStackPush(States::GameOver);

    } else if (mWorld.hasPlayerReachedEnd()) {
        mPlayer.setStatus(Player::Success);
        // requestStackPush(States::GameOver);
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
