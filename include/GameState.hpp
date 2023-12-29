#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Player.hpp"
#include "State.hpp"
#include "World.hpp"

class GameState : public State {
   public:
    GameState(StateStack& stack, Context& context);

    void save();
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event);

    Config::Game::Level getGameType() const;

   private:
    bool updateHighScore();
    void setupCountDown(Context& context);

   private:
    World mWorld;
    Player& mPlayer;
    std::vector<int>* mHighScores;
    Animation::Ptr mCountDown;
};

#endif  // GAME_STATE_HPP
